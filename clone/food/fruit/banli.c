// banli.c

#include <ansi.h>
inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIY "板栗" NOR, ({"ban li", "banli"}));
	set_weight(4000);
	set("long", "一捧肥大的板栗。\n");
	set("unit", "捧");
	set("value", 0);
	set("fruit_remaining", 8);
	set("food_supply", 23);
	set("water_supply", 1);
	set("eat_msg", "$N拿起$n，掰开外面的壳，香甜地吃起里面的栗子来。\n");
	set("end_msg", "$N把剩下的$n吃了个干净。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "con":1,
	]));
	setup();
}
