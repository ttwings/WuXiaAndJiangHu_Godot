//bamboo.c
//created 5-30-97 pickle

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
	set_name("短竹", ({"bamboo piece", "mace", "bamboo", "piece"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "根");
		set("value", 100);
		set("material", "wood");
		set("long", "一根短竹，大概是因为浸过水的原故拿在手里沉甸甸的。\n");
		set("wield_msg", "$N操起一根$n，摆了个架式。\n");
		set("unwield_msg", "$N将$n别回腰间。\n");
	}

	init_mace(5);
	setup();
}
