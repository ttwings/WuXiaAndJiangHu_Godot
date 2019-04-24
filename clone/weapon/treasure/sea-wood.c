// sea-wood.c 南海神木
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIC "南海神木" NOR, ({"sea wood", "wood", "sword"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "根");
		set("long", "这是一根遍体发出青光的剑形木棍。\n");
		set("value", 2000);
		set("material", "wood");
		set("wield_msg", "$N从背后将南海神木拔出来，拿在手中。\n");
		set("unwield_msg", "$N将手中的$n重新插回背后。\n");
	}
	init_sword(100);
	setup();
}
