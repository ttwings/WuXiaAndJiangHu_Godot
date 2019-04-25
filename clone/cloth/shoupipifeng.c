// shoupipifeng.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit SURCOAT;

void create()
{
	set_name("兽皮披风", ({"shoupi pifeng", "pifeng", "cloth"}));
	set_weight(4500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一件兽皮披风。\n");
		set("material", "leather");
		set("unit", "件");
		set("value", 700);
		set("armor_prop/armor", 35);
	}
	setup();
}
