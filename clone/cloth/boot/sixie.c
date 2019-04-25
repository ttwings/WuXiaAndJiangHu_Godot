// sixie.c  麻鞋

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name("丝鞋", ({"si xie", "shoes"}));
	set_weight(1200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("value", 300);
		set("unit", "双");
		set("material", "cloth");
		set("armor_prop/armor", 2);
	}
	setup();
}
