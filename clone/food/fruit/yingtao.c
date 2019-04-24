// yingtao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIR "樱桃" NOR, ({"ying tao", "yingtao", "cherry"}));
	set_weight(100);
	set("long", "一捧鲜红的樱桃，鲜艳欲滴。\n");
	set("unit", "捧");
	//	set("value", 20);
	set("life", 4);
	set("fruit_remaining", 5);
	set("food_supply", 10);
	set("water_supply", 10);
	set("eat_msg", "$N拿起$n，往嘴里丢了一颗\n");
	set("end_msg", "$N吃光了最后一颗$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "spi":1,
	]));
	setup();
}
