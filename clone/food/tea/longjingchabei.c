// longjingchabei.c
// Last Modified by winder on May. 29 2001

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("龙井茶杯", ({"longjing chabei", "cha", "chabei"}));
	set_weight(120);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一杯新沏的龙井茶，悠悠地冒着香气~~~~~~\n");
		set("unit", "杯");
		set("value", 40);
		set("remaining", 10);
		set("drink_supply", 20);
	}
	set("liquid", ([
							 "type":"tea",
							 "name":"茶",
						"remaining":15,
					  "drunk_apply":5,
	]));
}
