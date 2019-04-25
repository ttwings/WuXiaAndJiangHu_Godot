// beixin.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("皮背心", ({"pi beixin", "beixin"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一件水牛皮制的背心，虽不精致，但很结实。\n");
		set("unit", "件");
		set("value", 400);
		set("material", "leather");
		set("armor_prop/armor", 6);
	}
	setup();
}
