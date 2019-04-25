// gongqun.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("宫裙", ({"gong qun", "skirt"}));
	set_weight(2700);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一袭长长宫裙．\n");
		set("unit", "袭");
		set("value", 1000);
		set("material", "cloth");
		set("armor_prop/armor", 5);
		set("armor_prop/dodge", 10);
	}
	setup();
}
