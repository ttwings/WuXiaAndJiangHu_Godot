// sifeng_kuanxue.c 四缝宽靴

#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("四缝宽靴", ({"sifeng kuanxue", "xie", "shoes"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一双缝制精细的厚底布鞋，舒适合脚。\n");
		set("unit", "双");
		set("value", 500);
		set("material", "cloth");
		set("armor_prop/armor", 3);
		set("armor_prop/dodge", 3);
	}
	setup();
}
