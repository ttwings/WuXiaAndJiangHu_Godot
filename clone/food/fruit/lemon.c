// lemon.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIG "柠檬" NOR, ({"ning meng", "ningmeng", "lemon"}));
	set_weight(4000);
	set("long", "一个黄绿色的柠檬。\n");
	set("unit", "个");
	set("life", 5);
	set("value", 0);
	set("fruit_remaining", 2);
	set("food_supply", 10);
	set("water_supply", 40);
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，剥开皮，大大的咬了一口，哇～～酸死了！救命啊！\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N皱着眉头吃完了这个$n。\n");
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "int":1,
					 "per":1,
					 "spi":1,
	]));
	setup();
}
