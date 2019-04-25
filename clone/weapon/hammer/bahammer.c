// bahammer.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
	set_name("八宝铜锤", ({"hammer"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "这是一把沉重的铜锤，打造的相当坚实。没有千斤力气是拿不起的。\n");
		set("value", 1200);
		set("material", "iron");
		set("wield_msg", "$N拿出一把$n，试了试重量，然后握在手中。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
	}
	init_hammer(35);
	setup();
}
