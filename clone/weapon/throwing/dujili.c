// dujili.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit THROWING;

void create()
{
	set_name("毒蒺黎", ({"poison dart", "dart"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("base_unit", "枝");
		set("long", "铁打的蒺黎锋利无比，刃上闪现绿色，显是喂了毒药。\n");
		set("base_weight", 40);
		set("value", 0);
		set("base_value", 5);
	}
	set_amount(20);
	init_throwing(15);
	setup();
}
