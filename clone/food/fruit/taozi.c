// taozi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIM "桃子" NOR, ({"tao zi", "taozi", "peach"}));
	set_weight(4000);
	set("long", "一个大大的歪着嘴笑的大胖桃。\n");
	set("unit", "个");
	set("life", 5);
	set("value", 0);
	set("fruit_remaining", 2); //可以吃6口
	set("food_supply", 10);	//每口加10的food
	set("water_supply", 30);   //每口可以加10的water
	set("eat_msg", "$N拿起$n，大大的啃了一口。\n");
	set("end_msg", "$N仔细的啃完了这个$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("core", "桃核");									  //name
	set("core_id", ({"tao hu", "peach core", "core", "hu"})); //id
	set("core_unit", "个");									  //unit
	set("core_long", "一个啃得干干净净的桃核。\n");			  //long
	set("gifts", ([
					 "per":1,
					 "int":1,
	]));
	setup();
}
