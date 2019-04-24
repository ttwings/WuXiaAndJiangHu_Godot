// hat.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit HEAD;

void create()
{
	set_name("Õ±Ã±", ({"zhan mao", "hat"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¶¥");
		set("material", "cloth");
		set("value", 100);
		set("armor_prop/armor", 2);
	}
	setup();
}
