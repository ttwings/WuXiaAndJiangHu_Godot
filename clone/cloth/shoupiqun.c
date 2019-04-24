// shoupiqun.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(" ﬁ∆§»π", ({"shoupi qun", "cloth"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "“ªÃı ﬁ∆§»π°£\n");
		set("material", "leather");
		set("unit", "Ãı");
		set("value", 300);
		set("armor_prop/armor", 15);
	}
	setup();
}
