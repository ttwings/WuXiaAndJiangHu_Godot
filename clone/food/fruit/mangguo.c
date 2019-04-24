// mangguo.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIY "芒果" NOR, ({"mang guo", "mangguo"}));
	set_weight(4000);
	set("long", "一个大大的黄澄澄的芒果。\n");
	set("unit", "个");
	set("life", 3);
	set("value", 0);
	set("fruit_remaining", 5);
	set("food_supply", 15);
	set("water_supply", 5);
	set("eat_msg", "$N拿起$n，剥开皮，大大的啃了一口。\n");
	set("end_msg", "$N仔细的啃完了这个$n。\n");
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("core", "芒果核");							//name
	set("core_id", ({"mangguo hu", "hu", "core"})); //id
	set("core_unit", "个");							//unit
	set("core_long", "一个芒果核。\n");				//long
	set("gifts", ([
					 "con":1,
					 "per":1,
					 "spi":1,
	]));
	setup();
}
