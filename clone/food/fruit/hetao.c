// hetao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(YEL "核桃" NOR, ({"he tao", "hetao"}));
	set_weight(4000);
	set("long", "一捧皱巴巴的核桃。\n");
	set("unit", "捧");
	set("value", 0);
	set("fruit_remaining", 8);
	set("food_supply", 23);
	set("water_supply", 1);
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，小心地敲碎外面的壳，吃起里面的仁来。\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N把剩下的$n吃了个干净。\n");
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "spi":2,
					 "int":2,
	]));
	setup();
}
