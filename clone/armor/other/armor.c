// armor.c
// Last Modified by winder on May. 25 2001

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("铠甲", ({"armor"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "iron");
		set("unit", "副");
		set("armor_prop/armor", 5);
	}
	setup();
}
