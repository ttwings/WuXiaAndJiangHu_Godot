// tongjia.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit ARMOR;

void create()
{
	set_name("熟铜甲", ({"bronze armor","tongjia","jia","armor"}));
	set_weight(50000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", "一件金灿灿的熟铜甲。\n");
		set("value", 5000);
		set("material", "steel");
		set("armor_prop/armor", 45);
		set("armor_prop/dodge", -15);
	}
	setup();
}
