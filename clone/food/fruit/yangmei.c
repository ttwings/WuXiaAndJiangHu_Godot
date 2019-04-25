// yangmei.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(RED "杨梅" NOR, ({"yang mei", "yangmei", "redbayberry"}));
	set_weight(4000);
	set("long", "一捧红艳艳的杨梅。\n");
	set("unit", "捧");
	set("value", 0);
	set("life", 3);
	set("fruit_remaining", 8);
	set("food_supply", 1);
	set("water_supply", 4);
	set("eat_msg", "$N拿起$n，往嘴里丢了一颗，“噗”地吐出核。\n");
	set("end_msg", "$N吃光了最后一颗$n，却觉得牙有点酸。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	/* 
	set("gifts", ([
		"per" : 1,
		"int" : 1,
		"spi" : 1,
	]));
*/
	setup();
}
