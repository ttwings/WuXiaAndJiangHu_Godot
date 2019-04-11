// boluo.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(YEL"菠萝"NOR, ({"bo luo","boluo","pineapple"}));
	set_weight(4000);
	set("long", "一个削了皮的大菠萝。\n");
	set("unit", "个");
	set("life", 15);
	set("value", 0);
	set("fruit_remaining", 5); //可以吃5口
	set("food_supply", 23);   //每口加5的food
	set("water_supply", 70);  //每口可以加5的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，大大的咬了一口。\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N啃完了$n。\n");  
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n"); 
	// 水果吃完剩下的东西 :-)
	set("core", "菠萝把儿");	 //name
	set("core_id", ({"boluo ba", "ba"}) ); //id
	set("core_unit", "个");	//unit
	set("core_long", "一个菠萝把儿。\n"); //long
	set("gifts", ([
		"per" : 1,
		"con" : 1,
	]));
	setup();
}

