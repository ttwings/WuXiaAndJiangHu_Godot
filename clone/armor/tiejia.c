// tiejia.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit ARMOR;

void create()
{
	set_name("铁甲", ({"iron armor", "tiejia", "jia", "armor"}));
	set_weight(40000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "件");
		set("long", "一件沉甸甸的铁甲。\n");
		set("value", 3000);
		set("material", "steel");
		set("armor_prop/armor", 40);
		set("armor_prop/dodge", -10);
	}
	setup();
}
