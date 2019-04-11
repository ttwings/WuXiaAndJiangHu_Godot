// lizi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
	set_name(MAG"李子"NOR, ({"li zi", "lizi","plum"}));
	set_weight(4000);
	set("long", "一个圆溜溜的大李子。\n");
	set("unit", "个");
	set("value", 0);
	set("fruit_remaining", 1); //可以吃6口
	set("food_supply", 5);   //每口加10的food
	set("water_supply", 25);  //每口可以加10的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，大大的啃了一口。\n"); 
	//最后一口的msg，没有亦可
	set("end_msg", "$N仔细的啃完了这个$n。\n");  
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n"); 
	// 水果吃完剩下的东西 :-)
	set("core", "李子核");	 //name
	set("core_id", ({"lizi hu", "plum core", "core", "hu"}) ); //id
	set("core_unit", "个");	//unit
	set("core_long", "一个啃得干干净净的李子核。\n"); //long
	setup();
}

