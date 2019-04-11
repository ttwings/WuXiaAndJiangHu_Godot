// turou.c Ò°ÍÃÈâ
// Last Modified by winder on Aug. 1 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("ÍÃÈâ", ({"tu rou", "tu"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "Ò»¿éÏÊÑªÁÜÀì·ÊµÄÒ°ÍÃÈâ¡£\n");
		set("unit", "¿é");
		set("value", 50);
		set("food_remaining", 4);
		set("food_supply", 50);
//		set("food_race","Ò°ÊŞ");
	}
}
