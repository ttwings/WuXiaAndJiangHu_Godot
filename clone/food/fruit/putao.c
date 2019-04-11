// putao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
	set_name(MAG"葡萄"NOR, ({"pu tao", "putao","grape"}));
	set_weight(4000);
	set("long", "一串晶莹可爱的葡萄。\n");
	set("unit", "串");
	set("life", 7);
	set("value", 0);
	set("fruit_remaining", 5); //可以吃10口
	//set("food_supply", 2);   //每口加2的food
	set("water_supply", 20);  //每口可以加5的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，摘了几粒吃下去。\n"); 
	//最后一口的msg，没有亦可
	set("end_msg", "$N吃完了这串$n。\n");  
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n"); 
	set("gifts", ([
		"per" : 1,
		"int" : 1,
	]));
	setup();
}

