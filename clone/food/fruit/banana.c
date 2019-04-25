// banana.c
#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(HIY "香蕉" NOR, ({"xiang jiao", "xiangjiao", "banana"}));
	set_weight(4000);
	set("long", "一根又粗又长，弯弯的剥开了皮的香蕉。\n");
	set("unit", "根");
	set("life", 7);
	set("value", 0);
	set("fruit_remaining", 4); //可以吃4口
	set("food_supply", 15);	//每口加15的food
	set("water_supply", 4);	//每口可以加4的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，大大的咬了一口。\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N三口两口吃完了这个$n。\n");
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	// 水果吃完剩下的东西 :-)
	set("core", "香蕉皮");											 //name
	set("core_id", ({"xiangjiao pi", "banana peel", "pi", "peel"})); //id
	set("core_unit", "个");											 //unit
	set("core_long", "一个香蕉皮。\n");								 //long
	set("gifts", ([
					 "int":1,
					 "spi":1,
					 "per":1,
	]));
	setup();
}
