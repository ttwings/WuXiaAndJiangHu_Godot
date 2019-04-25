// maxie.c  麻鞋

#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("麻鞋", ({"ma xie", "xie", "shoes"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一双麻绳编制的鞋子。\n");
		set("unit", "双");
		set("value", 5);
		set("material", "silk");
		set("armor_prop/armor", 1);
	}
	setup();
}
