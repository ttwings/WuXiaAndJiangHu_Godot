// beast.c 野兽
// Last Modified by winder on Aug. 1 2002

inherit F_DBASE;

#ifndef __BEAST__
#define __BEAST__

// A normal beast is at least 50 kg weight
#define BASE_WEIGHT 50000
#endif



mapping *combat_action = ({
([
	"action":	"$N扑上来张嘴往$n的$l狠狠地一咬",
	"damage":	50,
	"damage_type":	"咬伤",
]),
([
	"action":	"$N举起爪子往$n的$l抓了过去",
	"damage":	30,
	"damage_type":	"抓伤",
]),
([
	"action":	"$N跃起来用前掌往$n的$l猛地一拍",
	"damage":	30,
	"damage_type":	"瘀伤",
]),
});

void create()
{
	seteuid(getuid());
	set("attitude", "aggressive");
	set("limbs", ({
		"头部",	"颈部",	"胸部",	"后背",	"腹部",	
		"前腿",	"后腿", "前爪",	"后爪", "尾巴"
	}) );

	set("dead_message", "\n$N仰天惨嚎了一声，趴在地上不动了。\n\n");
	set("unconcious_message", "\n$N低低地吼了一声，滚倒在地晕了过去。\n\n");
	set("revive_message", "\n$N四肢慢慢动弹了一下，睁开眼醒了过来。\n\n");
	set("comeout_message", "往$d奔了过去。\n");
	set("comein_message", "呼地窜了出来，警惕地四周张望着。\n");
	set("fleeout_message", "惨叫一声，往$d落荒而逃。\n");
	set("fleein_message", "摇摇摆摆地跑了过来，伸出舌头呼呼地喘着粗气。\n");
}

void setup_beast(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	my["unit"] = "只";
	
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) my["age"] = random(40) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random(40) + 5;
	if( undefinedp(my["int"]) ) my["int"] = random(10) + 5;
	if( undefinedp(my["per"]) ) my["per"] = random(30) + 5;
	if( undefinedp(my["con"]) ) my["con"] = random(40) + 5;
	if( undefinedp(my["dex"]) ) my["dex"] = random(40) + 5;
	if( undefinedp(my["kar"]) ) my["kar"] = random(20) + 5;

	if( undefinedp(my["max_jing"]) ) {
		if( my["age"] <= 3 ) my["max_jing"] = 50;
		else if( my["age"] <= 10 ) my["max_jing"] = 50 + (my["age"] - 3) * 20;
		else if( my["age"] <= 30 ) my["max_jing"] = 190 + (my["age"] - 10) * 5;
		else my["max_jing"] = 290 + (my["age"] - 30) * 2;
	}
	if( undefinedp(my["max_qi"]) ) {
		if( my["age"] <= 5 ) my["max_qi"] = 50;
		else if( my["age"] <= 20 ) my["max_qi"] = 50 + (my["age"] - 5) * 25;
		else my["max_qi"] = 425 + (my["age"] - 20) * 5;
	}
	if( undefinedp(my["max_jingli"]) ) {
		if( my["age"] <= 3 ) my["max_jingli"] = 100;
		else if( my["age"] <= 20 ) my["max_jingli"] = 100 + (my["age"] - 3) * 50;
		else my["max_jingli"] = 950 + (my["age"] - 20) * 10;
	}
	ob->set_default_object(__FILE__);
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
	return combat_action[random(sizeof(combat_action))];
}
