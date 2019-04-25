// bang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STICK;

void create()
{
	set_name("木杖", ({"bang"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("value", 400);
		set("material", "wood");
		set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
	}
	init_stick(20);
	setup();
}
