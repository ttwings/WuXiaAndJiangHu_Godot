// Last Modified by Winder on May. 21 2001
// muchui.c 木锤

#include <weapon.h>

inherit HAMMER;

void create()
{
	set_name("木锤", ({"muchui", "chui"}));
	set_weight(350);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一根削得很精致的短锤。\n");
		set("unit", "根");
		set("value", 100);
		set("wield_msg", "$N抓起一根$n，握在手中当武器。\n");
		set("material", "wood");
	}
	init_hammer(1);
	setup();
}
