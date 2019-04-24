// shizi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(YEL "柿子" NOR, ({"shi zi", "shizi", "persimmon"}));
	set_weight(4000);
	set("long", "一个黄澄澄的大柿子。\n");
	set("unit", "个");
	set("life", 10);
	set("value", 0);
	set("fruit_remaining", 2); //可以吃5口
	set("food_supply", 15);	//每口加5的food
	set("water_supply", 15);   //每口可以加5的water
	set("eat_msg", "$N拿起$n，大大的咬了一口。\n");
	set("end_msg", "$N吃完了$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("core", "柿子皮");						  //name
	set("core_id", ({"shizi pi", "pi", "peel"})); //id
	set("core_unit", "个");						  //unit
	set("core_long", "一个柿子皮。\n");			  //long
	set("gifts", ([
					 "per":1,
	]));
	setup();
}
