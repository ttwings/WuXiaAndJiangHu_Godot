// hongzao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(RED "红枣" NOR, ({"hong zao", "hongzao"}));
	set_weight(4000);
	set("long", "一把红红的大枣。\n");
	set("unit", "把");
	set("value", 0);
	set("fruit_remaining", 18);
	set("food_supply", 2);
	set("water_supply", 1);
	set("eat_msg", "$N拿起$n，丢了一颗到嘴里，“噗”的一声吐出枣核。\n");
	set("end_msg", "$N把剩下的$n吃了个干净。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	setup();
}
