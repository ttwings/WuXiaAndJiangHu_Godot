// pipa.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(YEL "枇杷" NOR, ({"pi pa", "pipa"}));
	set_weight(4000);
	set("long", "一束黄澄澄的枇杷，惹人流口水。\n");
	set("unit", "束");
	set("life", 5);
	set("value", 0);
	set("fruit_remaining", 4);
	set("food_supply", 12);
	set("water_supply", 24);
	set("eat_msg", "$N拿起$n，剥了皮，丢了一颗到嘴里，“噗”的一声吐出核。\n");
	set("end_msg", "$N把剩下的$n吃了个干净。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "spi":1,
					 "int":1,
					 "con":1,
					 "per":1,
	]));
	setup();
}
