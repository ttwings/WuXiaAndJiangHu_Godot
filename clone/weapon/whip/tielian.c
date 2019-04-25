// tielian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit WHIP;

void create()
{
	set_name("铁链", ({"tie lian", "lian", "whip"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一条长长的铁链，上面沾满了血．\n");
		set("unit", "条");
		set("value", 500);
	}
	init_whip(25);
	setup();
}
