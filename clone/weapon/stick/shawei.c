// shawei.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STICK;

void create()
{
	set_name("É±Íþ´ó°ô", ({"shawei bang", "bang"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "°Ñ");
		set("value", 200);
		set("material", "wood");
	}
	init_stick(20);
	setup();
}
