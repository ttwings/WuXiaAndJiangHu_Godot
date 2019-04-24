// guiyuan.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(MAG "桂圆" NOR, ({"gui yuan", "guiyuan", "longan"}));
	set_weight(4000);
	set("long", "一捧圆溜溜的桂圆。\n");
	set("unit", "捧");
	set("life", 30);
	set("value", 0);
	set("fruit_remaining", 8);
	set("food_supply", 1);
	set("water_supply", 4);
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，剥了皮，往嘴里丢了一颗，“噗”地吐出核。\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N吃光了最后一颗$n。\n");
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "int":2,
					 "con":1,
	]));
	setup();
}
