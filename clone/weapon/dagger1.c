// gangjian.c

#include <weapon.h>
inherit DAGGER;

void create()
{
	set_name("普通匕首", ({"dagger", "bishou"}));
	set_weight(6000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "这是一把比武专用的的匕首。\n");
		set("value", 0);
		set("material", "steel");
		set("wield_msg", "$N从兜里掏出一把$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n放会兜里。\n");
	}
	init_dagger(100, 0);
	setup();
}
