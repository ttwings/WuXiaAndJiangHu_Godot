// dart.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit THROWING;

void create()
{
	set_name("毒镖", ({"biao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long",
			"飞镖是一种十分常见的暗器，而毒镖却只有一个人有．\n");
		set("unit", "些");
		set("base_unit", "枝");
		set("base_weight", 40);
		set("base_value", 0);
	}
	set("value", 0);
	set_amount(30);
	init_throwing(20);
	setup();
}
