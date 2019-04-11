// gucui.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
	set_name("¹Ä´¸", ({"guchui", "hammer"}));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¸ö");
	}
	init_hammer(1);
	setup();
}

