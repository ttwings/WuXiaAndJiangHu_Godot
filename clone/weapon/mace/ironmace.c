//ironmace.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
	set_name("铁鞭", ({"iron mace", "mace", "ironmace"}));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "根");
		set("value", 1000);
		set("material", "iron");
		set("long", "一柄普通的竹节鞭。\n");
		set("wield_msg", "$N操起一根$n，摆了个架式。\n");
		set("unwield_msg", "$N将$n别回腰间。\n");
	}

	init_mace(15);
	setup();
}
