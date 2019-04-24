// boots.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name("Ñ¥×Ó", ({"boots"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "leather");
		set("unit", "Ë«");
		set("armor_prop/armor", 1);
	}
	setup();
}
