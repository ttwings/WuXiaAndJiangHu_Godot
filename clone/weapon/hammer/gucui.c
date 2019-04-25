// gucui.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
	set_name("鼓锤", ({"guchui", "hammer"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "个");
	}
	init_hammer(1);
	setup();
}
