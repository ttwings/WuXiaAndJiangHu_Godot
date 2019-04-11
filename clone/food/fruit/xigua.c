// xigua.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
	set_name(GRN"西瓜"NOR, ({"xi gua", "xigua","watermelon"}));
	set_weight(8000);
	set("long", "一块切好了的西瓜，黑籽红瓤，嘿～～快吃吧！\n");
	set("unit", "块");
	set("value", 0);
	set("fruit_remaining", 2); //可以吃5口
	set("food_supply", 13);   //每口加5的food
	set("water_supply", 27);  //每口可以加5的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，大大的咬了一口，爽啊～～\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N啃完了$n，“噗噗噗”吐出一堆西瓜籽来。\n");  
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n"); 
	// 水果吃完剩下的东西 :-)
	set("core", "西瓜皮");	 //name
	set("core_id", ({"xigua pi", "pi", "peel"}) ); //id
	set("core_unit", "块");	//unit
	set("core_long", "一块西瓜皮。\n"); //long
	set("gifts", ([
		"per" : 1,
		"spi" : 1,
	]));
	setup();
}

