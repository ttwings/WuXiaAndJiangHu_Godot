// caomei.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIR "草莓" NOR, ({"cao mei", "caomei", "stawberry"}));
	set_weight(4000);
	set("long", "一捧鲜红的草莓，鲜艳欲滴。\n");
	set("unit", "捧");
	set("life", 3);
	set("value", 0);
	set("fruit_remaining", 8);
	set("food_supply", 1);
	set("water_supply", 3);
	set("eat_msg", "$N拿起$n，往嘴里丢了一颗\n");
	set("end_msg", "$N吃光了最后一颗$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	setup();
}
