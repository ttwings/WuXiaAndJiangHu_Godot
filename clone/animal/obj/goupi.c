// goupi.c
// Last Modified by winder on Aug. 1 2002

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name(YEL "¹·Æ¤" NOR, ({"gou pi", "pi"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¿é");
		set("material", "fur");
		set("value", 100);
		set("armor_prop/armor", 1);
	}
	setup();
}
