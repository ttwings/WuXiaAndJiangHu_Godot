// jingua.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
	set_name("金瓜", ({"golden hammer", "gua", "hammer"}));
	set_weight(8500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "这是一把沉重的金瓜，是皇城卫士的专用武器。\n");
		set("value", 1200);
		set("material", "iron");
		set("wield_msg", "$N拿出一把$n，试了试重量，然后握在手中。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
	}
	init_hammer(25);
	setup();
}
