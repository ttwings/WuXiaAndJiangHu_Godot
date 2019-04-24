// sifeng_huangxue.c 四缝干黄靴

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name("四缝干黄靴", ({"sifeng huangxue", "xie", "shoes"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一双精心缝制的皮靴，轻便舒适。\n");
		set("unit", "双");
		set("value", 500);
		set("material", "pi");
		set("armor_prop/armor", 4);
		set("armor_prop/dodge", 10);
	}
	setup();
}
