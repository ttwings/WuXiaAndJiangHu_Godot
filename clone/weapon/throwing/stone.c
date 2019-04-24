// stone.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit THROWING;

void create()
{
	set_name("飞蝗石", ({"shi"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "飞蝗石是一种十分常见的暗器。\n");
		set("unit", "些");
		set("base_value", 0);
		set("base_unit", "块");
		set("base_weight", 50);
		set("value", 0);
	}
	set("value", 0);
	set_amount(20);
	init_throwing(20);
	setup();
}
