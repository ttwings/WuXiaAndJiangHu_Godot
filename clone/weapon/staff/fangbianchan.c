// Last Modified by Winder on May. 25 2001
// fangbianchan.c

#include <weapon.h>
inherit STAFF;

void create()
{
	set_name("方便铲", ({"fangbianchan", "fangbian", "chan"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "条");
		set("value", 5);
		set("material", "wood");
		set("long", "一条非常粗大结实的方便铲。\n");
		set("wield_msg", "$N拿起一根$n，在手中掂量掂量。\n");
		set("unwield_msg", "$N哼了一声，将$n放回身后。\n");
	}
	init_staff(35);
	setup();
}
