// shield.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit SHIELD;

void create()
{
	set_name("∂‹≈∆", ({"shield"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "wood");
		set("unit", "√Ê");
		set("armor_prop/armor", 5);
	}
	setup();
}
