// stock.c 走畜
// Last Modified by winder on Aug. 1 2002

inherit F_DBASE;

#ifndef __LIVESTOCK__
#define __LIVESTOCK__

// A normal LIVESTOCK is at least 100 kg weight
#define BASE_WEIGHT 100000
#endif


mapping *combat_action = ({
([
	"action":	"$N用后腿往$n的$l用力一蹬",
	"damage":	30,
	"damage_type":	"瘀伤",
]),
([
	"action":	"$N低下头往$n的$l猛地一撞",
	"damage":	30,
	"damage_type":	"瘀伤",
]),
([
	"action":	"$N抬起前腿往$n的$l狠狠地一踢",
	"damage":	20,
	"damage_type":	"瘀伤",
]),
});

void create()
{
	seteuid(getuid());
	set("attitude", "friendly");
	set("limbs", ({
		"头部",	"颈部",	"胸部",	"后背",	"腹部",	
		"前腿",	"后腿", "前蹄",	"后蹄", "尾巴"
	}) );

	set("dead_message", "\n$N悲嘶一声，倒地挣扎了几下不动了。\n\n");
	set("unconcious_message", "\n$N长声悲嘶，乒地一声摔倒在地上。\n\n");
	set("revive_message", "\n$N慢慢动弹了一下，低嘶一声，站立起来。\n\n");
	set("comeout_message", "往$d驰去。\n");
	set("comein_message", "小步跑了过来，蹄声有节奏地踏击着地面。\n");
	set("fleeout_message", "悲嘶一声，往$d落荒而逃。\n");
	set("fleein_message", "摇摇摆摆地跑了过来，鼻孔里呼呼地喷着白气。\n");
}

void setup_stock(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	my["unit"] = "只";
	
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) my["age"] = random(30) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random(30) + 5;
	if( undefinedp(my["int"]) ) my["int"] = random(20) + 5;
	if( undefinedp(my["per"]) ) my["per"] = random(20) + 5;
	if( undefinedp(my["con"]) ) my["con"] = random(40) + 5;
	if( undefinedp(my["dex"]) ) my["dex"] = random(20) + 5;
	if( undefinedp(my["kar"]) ) my["kar"] = random(10) + 5;

	if( undefinedp(my["max_jing"]) )
	{
		if( my["age"] <= 3 ) my["max_jing"] = 50;
		else if( my["age"] <= 10 ) my["max_jing"] = 50 + (my["age"] - 3) * 20;
		else if( my["age"] <= 30 ) my["max_jing"] = 190 + (my["age"] - 10) * 5;
		else my["max_jing"] = 290 + (my["age"] - 30) * 2;
	}
	if( undefinedp(my["max_qi"]) ) {
		if( my["age"] <= 5 ) my["max_qi"] = 100;
		else if( my["age"] <= 20 ) my["max_qi"] = 100 + (my["age"] - 5) * 20;
		else my["max_qi"] = 400 + (my["age"] - 20) * 5;
	}
	if( undefinedp(my["max_jingli"]) ) {
		if( my["age"] <= 3 ) my["max_jingli"] = 150;
		else if( my["age"] <= 20 ) my["max_jingli"] = 150 + (my["age"] - 3) * 40;
		else my["max_jingli"] = 830 + (my["age"] - 20) * 10;
	}
	ob->set_default_object(__FILE__);
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
	return combat_action[random(sizeof(combat_action))];
}
