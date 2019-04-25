// gujia.c
// Last Modified by winder on May. 25 2001

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("兽骨甲", ({"shougu jia", "shougujia", "jia", "armor"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "件");
		set("long", "一件兽骨甲。\n");
		set("value", 2500);
		set("material", "bone");
		set("armor_prop/armor", 35);
	}
	setup();
}
