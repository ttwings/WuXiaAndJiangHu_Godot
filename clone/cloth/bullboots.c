// bullboot.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name("牛皮靴", ({"niupi xue", "leather boots", "boots"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "双");
		set("long", "一双皮靴，上等牛皮制成。\n");
		set("value", 400);
		set("material", "cloth");
		set("armor_prop/armor", 3);
	}
	setup();
}
