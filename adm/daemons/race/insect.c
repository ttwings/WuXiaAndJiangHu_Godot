// insect.c 昆虫
// Last Modified by winder on Aug. 1 2002

inherit F_DBASE;

#ifndef __INSECT__
#define __INSECT__

// A normal insect is at least 1 g weight
#define BASE_WEIGHT 1
#endif



mapping *combat_action_crawl = ({
([
	"action":	"$N爬上来张嘴往$n的$l狠狠地一咬",
	"damage":	30,
	"damage_type":	"咬伤",
]),
([
	"action":	"$N跃上来猛地往$n的$l叮了一下",
	"damage":	10,
	"damage_type":	"刺伤",
]),
([
	"action":	"$N反转身用尾巴尖对准$n的$l一刺",
	"damage":	20,
	"damage_type":	"刺伤",
]),
});

mapping *combat_action_fly = ({
([
	"action":	"$N飞过来张嘴往$n的$l狠狠地一咬",
	"damage":	30,
	"damage_type":	"咬伤",
]),
([
	"action":	"$N飞上来猛地往$n的$l叮了一下",
	"damage":	10,
	"damage_type":	"刺伤",
]),
([
	"action":	"$N反转身用尾巴尖对准$n的$l一刺",
	"damage":	20,
	"damage_type":	"刺伤",
]),
});

void create()
{
	seteuid(getuid());
	set("attitude", "heroism");
}

void setup_insect(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));
	
	my["unit"] = "只";
	
	if( undefinedp(my["gender"]) ) my["gender"] = "无性";
	if( undefinedp(my["age"]) ) my["age"] = random( 5) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random( 5) + 5;
	if( undefinedp(my["int"]) ) my["int"] = random( 5) + 5;
	if( undefinedp(my["per"]) ) my["per"] = random( 5) + 5;
	if( undefinedp(my["con"]) ) my["con"] = random(10) + 5;
	if( undefinedp(my["dex"]) ) my["dex"] = random(15) + 5;
	if( undefinedp(my["kar"]) ) my["kar"] = random(10) + 5;

	if( undefinedp(my["max_jing"]) ) {
		if( my["age"] <= 5 ) my["max_jing"] = my["age"] * 5;
		else my["max_jing"] = 25;
	}
	if( undefinedp(my["max_qi"]) ) {
		if( my["age"] <= 5 ) my["max_qi"] = my["age"] * 5;
		else my["max_qi"] = 25;
	}
	if( undefinedp(my["max_jingli"]) ) {
		if( my["age"] <= 5 ) my["max_jingli"] = my["age"] * 5;
		else my["max_jingli"] = 25;
	}
	ob->set_default_object(__FILE__);
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 5)* 100);

	if( ob->query("subrace") == "爬虫" )
	{
		set("dead_message", "\n$N四脚朝天地翻了过来，死了。\n\n");
		set("unconcious_message", "\n$N四脚朝天地翻了过来，不动了。\n\n");
		set("revive_message", "\n$N一下翻过身，又敏捷地四处爬动起来。\n\n");
		set("comeout_message", "唰地跃入草丛，往$d钻了出去。\n");
		set("comein_message", "爬了过来。\n");
		set("fleeout_message", "唰地跃入草丛，往$d钻了出去。\n");
		set("fleein_message", "缓缓爬了过来，动作有些迟滞。\n");

		set("limbs", ({"头部",	"背部",	"腹部", "触角", "前腿",	"后腿", "尾巴"}) );
	}

	if( ob->query("subrace") == "飞虫" )
	{
		set("dead_message", "\n$N掉在地上，挣扎了几下就死了。\n\n");
		set("unconcious_message", "\n$N扑的跌在地上，昏了过去。\n\n");
		set("revive_message", "\n$N张开翅膀扑腾了一下，又飞了起来。\n\n");
		set("comeout_message", "嗡嗡嗡地叫着往$d飞了出去。\n");
		set("comein_message", "嗡嗡地叫着飞了过来。\n");
		set("fleeout_message", "嗡嗡地叫着往$d飞了出去。\n");
		set("fleein_message", "缓缓飞了过来，动作有些迟滞。\n");

		set("limbs", ({"头部",	"背部",	"腹部",	"翅膀", "前腿",	"后腿", "尾巴"}) );
	}
}

mapping query_action(object me)
{
	if( me->query("subrace") == "爬虫" )
		return combat_action_crawl[random(sizeof(combat_action_crawl))];
	if( me->query("subrace") == "飞虫" )
		return combat_action_fly[random(sizeof(combat_action_fly))];
}
