// ganzhe.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
	set_name(MAG "甘蔗" NOR, ({"gan zhe", "ganzhe", "sugarcane"}));
	set_weight(4000);
	set("long", "一根又粗又长的甘蔗。\n");
	set("unit", "根");
	set("life", 30);
	set("value", 0);
	set("fruit_remaining", 15); //可以吃15口
	set("water_supply", 10);	//每口可以加10的water
	//每次吃的msg,没有也可以的。
	set("eat_msg", "$N拿起$n，狠狠的咬了一大口，咂了咂嘴。\n");
	//最后一口的msg，没有亦可
	set("end_msg", "$N仔细的啃完了这根$n。\n");
	//吃饱了的msg, 没有亦可，但不能有代词。
	set("over_msg", "吃这么多？小心撑破肚皮！！！！\n");
	set("gifts", ([
					 "per":1,
					 "con":1,
	]));
	setup();
}
