// juzi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(YEL "橘子" NOR, ({"ju zi", "juzi", "orange"}));
	set_weight(4000);
	set("long", "一个圆圆的金黄色的大橘子。\n");
	set("unit", "个");
	set("life", 20);
	set("value", 0);
	set("fruit_remaining", 3);
	set("food_supply", 5);
	set("water_supply", 25);
	set("eat_msg", "$N拿起$n，剥了几个瓣儿吃下去。\n");
	set("end_msg", "$N剥出最后一瓣$n吃下去。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("core", "橘子皮");
	set("core_id", ({"juzi pi", "orange peel", "pi", "peel"})); //id
	set("core_unit", "个");										//unit
	set("core_long", "一个橘子皮。\n");							//long
	set("gifts", ([
					 "per":1,
					 "int":1,
	]));

	setup();
}
