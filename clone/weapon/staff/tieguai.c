// tieguai.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STAFF;

void create()
{
	set_name("铁拐", ({"tie guai", "tieguai", "guai"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "根");
		set("long", "一条铁拐，看起来黑黝黝的，分量肯定不轻。\n");
		set("value", 1000);
		set("material", "steel");
	}

	init_staff(20);
	setup();
}
