// yangpi.c —Ú∆§
// Last Modified by winder on Aug. 1 2002

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("—Ú∆§", ({"yang pi", "pi", "lamb skin"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "øÈ");
		set("material", "fur");
		set("value", 400);
		set("armor_prop/armor", 3);
	}
	setup();
}
