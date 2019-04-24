// mabukuanshan.c 麻布宽衫

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("麻布宽衫", ({"mabu kuanshan", "cloth"}));
	set_weight(1500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一套灰色的麻布宽衫。\n");
		set("unit", "套");
		set("value", 300);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
