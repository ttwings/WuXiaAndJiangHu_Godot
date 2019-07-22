# /adm/daemons/race/human.c
# From ES2
# Modified by Xiang@XKX
# Modified by Zeratul Jan 6 2001
# Last Modified by winder on Aug. 1 2002

# A normal human is at least 40 kg weight

# inherit F_DBASE;
# inherit F_SKILL;

const BASE_WEIGHT = 40000



var combat_action = [
	{	"action":	"$N挥拳攻击$n的$l",
		"damage_type":	"瘀伤",
	},
	{	"action":	"$N往$n的$l一抓",
		"damage_type":	"抓伤",
	},
	{	"action":	"$N往$n的$l狠狠地踢了一脚",
		"damage_type":	"瘀伤",
	},
	{	"action":	"$N提起拳头往$n的$l捶去",
		"damage_type":	"内伤",
	},
	{	"action":	"$N对准$n的$l用力挥出一拳",
		"damage_type":	"瘀伤",
	},
];

func create():
	seteuid(getuid());
	set("unit", "位");
	set("gender", "男性");
	set("can_speak", 1);
	set("attitude", "peaceful");
	set("limbs", [
		"头顶", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
		"右臂", "左手", "右手", "两肋", "左脸", "腰间", "小腹",
		"左腿", "右腿", "右脸", "左脚", "右脚", "左耳", "右耳"
	] );

	set("dead_message", "\n$N倒在地上，挣扎了几下就死了。\n\n");
	set("unconcious_message", "\n$N脚下一个不稳，跌在地上昏了过去。\n\n");
	set("revive_message", "\n$N慢慢睁开眼睛，清醒了过来。\n\n");

func setup_human(ob):
	var my;
	var xism_age
	var i;

	my = ob.query_entire_dbase();
	# 调用文件对应的动作
	# ob.set("default_actions", (: call_other, __FILE__, "query_action" :));

	if( undefinedp(my["age"} ) :
		my["age"] = 14;
	if (undefinedp(my["str"] ):
		my["str"] = 10 + random(21);
	if (undefinedp(my["con"] ):
		my["con"] = 10 + random(21);
	if (undefinedp(my["dex"] ):
		my["dex"] = 10 + random(21);
	if (undefinedp(my["int"] ):
		my["int"] = 80 - my["str"] - my["con"] - my["dex"];
	if (undefinedp(my["per"] :
		my["per"] = 10 + random(21);
	if (undefinedp(my["kar"] :
		my["kar"] = 10 + random(21);
	if (undefinedp(my["sta"} || my["sta"]==0) :
		my["sta"] = 10 + random(21);
	if (undefinedp(my["cps"} || my["cps"]==0) :
		my["cps"] = 10 + random(21);
	if (undefinedp(my["cor"} || my["cor"]==0) :
		my["cor"] = 10 + random(21);

	if (undefinedp(my["max_tili"] :
		my["max_tili"] = my["sta"] * 5;
	if( userp(ob) || undefinedp(my["max_jing"} || my["max_jing"]<1 ):
		if( my["age"] <= 14 ) :
			my["max_jing"] = 100;
		elif( my["age"] <= 30 ) :
			my["max_jing"] = 100 + (my["age"] - 14) * my["int"];
		else :
			my["max_jing"] = my["int"] * 16 + 100;

		# Modified by zeratul Jan 6 2001
#		if( my["age"] > 60 ) my["max_jing"] -= (my["age"] - 60) * 5 ;
		if ( my["age"] > 60 ):
			i = my["age"] - 60;
			i = i * ( i + 1 ) / 2;
			my["max_jing"] -= i;

		# 道家保精：
		if(my["age"] > 60 && ob.query_skill("taoism", 1) >= 120):
			# Modified by zeratul Jan 6 2001
#			my["max_jing"] += (my["age"] - 60) * 5;
			my["max_jing"] += i;

		# 佛家养精：３０岁前补精，３０岁后长精
		if((xism_age=ob.query_skill("buddhism", 1)) > 39):
			xism_age = xism_age/2;
			if (my["age"] <= 30) :
				xism_age -= my["age"];
			else :
				xism_age -= 30;

			if (xism_age > 0) :
				my["max_jing"] += xism_age *(ob.query_skill("hunyuan-yiqi", 1)/10);

		# 紫氲吟长精：
		if((xism_age=ob.query_skill("ziyunyin", 1)) > 39) :
			xism_age = xism_age/2;
			xism_age -= 14;
			if (xism_age > 0) :
				my["max_jing"] += xism_age *(ob.query_skill("zixia-shengong", 1) / 20);

		if( my["max_jingli"] > 0 ) :
			my["max_jing"] += my["max_jingli"] / 4;
		# Modified by zeratul Jan 6 2001
		if ( my["max_jing"] < 1 ):
			my["max_jing"] = 1;		 
	
	if( userp(ob) || undefinedp(my["max_qi"} || my["max_qi"] < 1 ):
		if( my["age"] <= 14 ) :
			my["max_qi"] = 100;
		elif( my["age"] <= 30 ) :
			my["max_qi"] = 100 + (my["age"] - 14) * my["con"];
		else :
			my["max_qi"] = my["con"] * 16 + 100;

		# Modified by zeratul Jan 6 2001
#		if( my["age"] > 60 ) my["max_qi"] -= (my["age"] - 60) * 5;
		if ( my["age"] > 60 ):
			i = my["age"] - 60;
			i = i * ( i + 1 ) * 2;
			my["max_qi"] -= i;

		# 佛家保气：
		if(my["age"] > 60 && ob.query_skill("buddhism", 1) >= 120):
			# Modified by zeratul Jan 6 2001
#			my["max_qi"] += (my["age"] - 60) * 5;
			my["max_qi"] += i;

		# 道家正一派练气：３０岁前补气，３０岁后长气
		if((xism_age=ob.query_skill("taoism", 1)) > 39):
			xism_age = xism_age/2;
			if (my["age"] <= 30) :
				xism_age -= my["age"];
			else :
				xism_age -= 30;

			if (xism_age > 0) :
				my["max_qi"] += xism_age *(ob.query_skill("taiji-shengong", 1)/10);

		# 道家全真派练气：３０岁前补气，３０岁后长气
		if((xism_age=ob.query_skill("taoism", 1)) > 39):
			xism_age = xism_age/2;
			if (my["age"] <= 30) :
				xism_age -= my["age"];
			else :
				xism_age -= 30;

			if (xism_age > 0) :
				my["max_qi"] += xism_age *(ob.query_skill("xiantian-qigong", 1)/10);
		
		# 正气诀长气：
		if((xism_age=ob.query_skill("zhengqijue", 1)) > 39): 
		
			xism_age = xism_age/2;
			xism_age -= 14;

			if (xism_age > 0) :
				my["max_qi"] += xism_age *(ob.query_skill("zixia-shengong", 1) / 20);
		
		# 毒技练气：３０岁前补气，３０岁后长气
		if((xism_age=ob.query_skill("poison", 1)) > 39):
		
			xism_age = xism_age/2;
			if (my["age"] <= 30) :
				xism_age -= my["age"];
			else :
				xism_age -= 30;

			if (xism_age > 0) :
				my["max_qi"] += xism_age *(ob.query_skill("huagong-dafa", 1)/10);
		

		if( my["max_neili"] > 0 ) :
			my["max_qi"] += my["max_neili"] / 4;

		# Modified by zeratul Jan 6 2001
		if ( my["max_qi"] < 1 ):
			my["max_qi"] = 1;		
	

	ob.set_default_object(__FILE__);
	if( !ob.query_weight() ) :
		ob.set_weight(BASE_WEIGHT + (my["str"] - 10)*2000);


var query_action():
	return combat_action[random(sizeof(combat_action))];

