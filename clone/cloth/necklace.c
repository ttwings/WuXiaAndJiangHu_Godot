// necklace.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit NECK;

void create()
{
	set_name("项链", ({"xiang lian", "necklace"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "串");
		set("material", "pearl");
		set("value", 100);
		set("armor_prop/armor", 2);
	}
	setup();
}
