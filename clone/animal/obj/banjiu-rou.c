// banjiu-rou.c °ßð¯Èâ
// Last Modified by winder on Aug. 1 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("°ßð¯Èâ", ({"banjiu rou", "bird meat"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "Ò»Ö»ËÀµÄ°ßð¯¡£\n");
		set("unit", "Ö»");
		set("value", 20);
		set("food_remaining", 1);
		set("food_supply", 40);
//		set("food_race","Ò°ÊÞ");
	}
}
