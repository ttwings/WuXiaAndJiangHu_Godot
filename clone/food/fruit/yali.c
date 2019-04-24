// yali.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIY "鸭梨" NOR, ({"ya li", "yali", "pear"}));
	set_weight(4000);
	set("long", "一个大大的脆生生黄澄澄的鸭梨。\n");
	set("unit", "个");
	set("life", 7);
	set("value", 0);
	set("fruit_remaining", 2); //可以吃5口
	set("food_supply", 15);	//每口加5的food
	set("water_supply", 25);   //每口可以加15的water
	set("eat_msg", "$N拿起$n，大大的啃了一口。\n");
	set("end_msg", "$N仔细的啃完了这个$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("core", "梨核");									//name
	set("core_id", ({"li hu", "pear core", "hu", "core"})); //id
	set("core_unit", "个");									//unit
	set("core_long", "一个啃得干干净净的梨核。\n");			//long
	set("gifts", ([
					 "per":1,
					 "int":1,
	]));
	setup();
}
