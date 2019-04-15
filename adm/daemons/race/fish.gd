# fish.c 游鱼
# Last Modified by winder on Aug. 1 2002

# inherit F_DBASE;

#ifndef __FISH__
#define __FISH__

# A normal fish is at least 20 g weight
#define BASE_WEIGHT 20
#endif

const BASE_WEIGHT 20


var combat_action = [
{
	"action":	"$N游上来来张嘴往$n的$l狠狠地一咬",
	"damage":	20,
	"damage_type":	"咬伤",
},
{
	"action":	"$N摆动尾巴往$n的$l猛地一拍",
	"damage":	20,
	"damage_type":	"淤伤",
},
];

func create():
	seteuid(getuid());
	set("attitude", "peaceful");
	set("limbs", [
		"头部",	"腮部",	"背部",	"腹部",	
		"前鳍",	"后鳍", "尾巴"
	] );

	set("dead_message", "\n$N摆动了几下，白白的肚子往上翻了起来。\n\n");
	set("unconcious_message", "\n$N摆动了几下，红红的腮帮往外翻了出来。\n\n");
	set("revive_message", "\n$N摆了几下，又在水中游了开去。\n\n");
	set("comeout_message", "打了个水漂，往$d游了出去。\n");
	set("comein_message", "游了过来，在水中灵活地打了个转儿。\n");
	set("fleeout_message", "打了个水漂，往$d游了出去。\n");
	set("fleein_message", "摇头摆尾地游了过来，白白的肚子往上翻着。\n");


func setup_fish(ob):
	var my;

	my = ob.query_entire_dbase();

	ob.set("default_actions", (: call_other, __FILE__, "query_action" :));

	my["unit"] = "条";
	
	if( undefinedp(my["gender"]) ) :
		my["gender"] = "无性";
	if( undefinedp(my["age"]) ) :
		my["age"] = random(5) + 5;
	if( undefinedp(my["str"]) ) :
		my["str"] = random(10) + 5;
	if( undefinedp(my["int"]) ) :
		my["int"] = random( 5) + 5;
	if( undefinedp(my["per"]) ) :
		my["per"] = random( 5) + 5;
	if( undefinedp(my["con"]) ) :
		my["con"] = random(10) + 5;
	if( undefinedp(my["dex"]) ) :
		my["dex"] = random(20) + 5;
	if( undefinedp(my["kar"]) ) :
		my["kar"] = random(10) + 5;

	if( undefinedp(my["max_jing"]) ) :
		if( my["age"] <= 10 ) :
			my["max_jing"] = my["age"] * 5;
		else :
			my["max_jing"] = 50;
	
	if( undefinedp(my["max_qi"]) ) :
		if( my["age"] <= 10 ) :
			my["max_qi"] = my["age"] * 8;
		else :
			my["max_qi"] = 80;
	
	if( undefinedp(my["max_jingli"} ) :
		if( my["age"] <= 10 ) :
			my["max_jingli"] = my["age"] * 10;
		else :
			my["max_jingli"] = 100;
	
	ob.set_default_object(__FILE__);
	if( !ob.query_weight() ) :
		ob.set_weight(BASE_WEIGHT + (my["str"] - 5)* 500);


func query_action(me):
	return combat_action[random(sizeof(combat_action))];

