// baodi_kuaixue.c

#include <armor.h>
inherit BOOTS;
void create()
{
	set_name("薄底快靴", ({"baodi kuaixue", "xue", "shoes"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这双靴子缝制精细，轻便灵巧，武林人士常传这种靴子。\n");
		set("unit", "双");
		set("value", 200);
		set("material", "silk");
		set("armor_prop/armor", 1);
		set("armor_prop/dodge", 10);
	}
	setup();
}
