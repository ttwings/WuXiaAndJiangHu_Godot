// yangrou.c 羊肉
// Last Modified by winder on Aug. 1 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("羊肉", ({"yang rou", "lamb"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一块羔羊坐臀。\n");
		set("unit", "块");
		set("value", 80);
		set("food_remaining", 4);
		set("food_supply", 50);
	}
}
