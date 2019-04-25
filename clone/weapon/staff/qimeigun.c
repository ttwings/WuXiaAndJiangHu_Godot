// qimeigun.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STAFF;

void create()
{
	set_name("齐眉棍", ({"qimeigun", "gun", "bang"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "条");
		set("value", 5);
		set("material", "wood");
		set("long", "一根非常结实的齐眉棍。\n");
		set("wield_msg", "$N拿起一根$n，顺手舞了个棍花。\n");
		set("unwield_msg", "$N哼了一声，将$n插回后腰。\n");
	}
	init_staff(18);
	setup();
}
