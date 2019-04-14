// bird.c 飞禽
// Last Modified by winder on Aug. 1 2002

inherit F_DBASE;

#ifndef __BIRD__
#define __BIRD__

// A normal bird is at least 50 g weight
#define BASE_WEIGHT 50
#endif



mapping *combat_action = ({
([
	"action":	"$N用爪子往$n的$l猛地一抓",
	"damage":	10,
	"damage_type":	"抓伤",
]),
([
	"action":	"$N飞过来往$n的$l狠狠地一啄",
	"damage":	30,
	"damage_type":	"刺伤",
]),
([
	"action":	"$N用翅膀向$n的$l拍了过去",
	"damage":	30,
	"damage_type":	"刺伤",
])
});

void create()
{
	seteuid(getuid());
	set("attitude", "peaceful");
	set("limbs", ({
		"头部",	"颈部",	"后背",	"腹部",	"脚爪",	"翅膀"
	}) );

	set("dead_message", "\n$N发出一声凄厉的鸣叫，从半空中跌了下来。\n\n");
	set("unconcious_message", "\n$N从半空中砰地跌下来，晕了过去。\n\n");
	set("revive_message", "\n$N醒过来动弹了一下，双翅一振，又飞了起来。\n\n");
	set("comeout_message", "往$d疾飞而去。\n");
	set("comein_message", "飞了过来。\n");
	set("fleeout_message", "一声凄鸣，往$d疾飞而去。\n");
	set("fleein_message", "缓缓地飞了过来，沉重地在半空中打着旋儿。\n");
}

void setup_bird(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	my["unit"] = "只";
	
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) my["age"] = random(20) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random(10) + 5;
	if( undefinedp(my["int"]) ) my["int"] = random(10) + 5;
	if( undefinedp(my["per"]) ) my["per"] = random(20) + 5;
	if( undefinedp(my["con"]) ) my["con"] = random(50) + 5;
	if( undefinedp(my["dex"]) ) my["dex"] = random(60) + 5;
	if( undefinedp(my["kar"]) ) my["kar"] = random(20) + 5;

	if( undefinedp(my["max_jing"]) ) {
		if( my["age"] <= 3 ) my["max_jing"] = 30;
		else if( my["age"] <= 10 ) my["max_jing"] = 30 + (my["age"] - 3) * 10;
		else if( my["age"] <= 30 ) my["max_jing"] = 100 + (my["age"] - 10) * 3;
		else my["max_jing"] = 160 + (my["age"] - 30);
	}
	if( undefinedp(my["max_qi"]) ) {
		if( my["age"] <= 5 ) my["max_qi"] = 30;
		else if( my["age"] <= 20 ) my["max_qi"] = 30 + (my["age"] - 5) * 15;
		else my["max_qi"] = 255 + (my["age"] - 20) * 5;
	}
	if( undefinedp(my["max_jingli"]) ) {
		if( my["age"] <= 5 ) my["max_jingli"] = 20;
		else if( my["age"] <= 20 ) my["max_jingli"] = 20 + (my["age"] - 5) * 20;
		else my["max_jingli"] = 320 + (my["age"] - 20) * 5;
	}
	ob->set_default_object(__FILE__);
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 5)* 1000);

	if( ob->query("subrace") == "走禽" )
	{
		set("dead_message", "\n$N发出一声凄厉的鸣叫，栽倒在地上死了。\n\n");
		set("unconcious_message", "\n$N凄鸣一声栽倒在地，晕了过去。\n\n");
		set("revive_message", "\n$N醒过来动弹了一下，双翅扑腾了几下站了起来。\n\n");
		set("comeout_message", "往$d疾奔而去。\n");
		set("comein_message", "跑了过来。\n");
		set("fleeout_message", "一声凄鸣，往$d疾奔而去。\n");
		set("fleein_message", "摇摇摆摆的跑了过来。\n");
	}
}

mapping query_action(object me)
{
	return combat_action[random(sizeof(combat_action))];
}

