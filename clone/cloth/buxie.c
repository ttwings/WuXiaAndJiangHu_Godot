// buxie.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name("Բ�ڲ�Ь", ({"yuankou buxie", "bu xie", "shoes"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "˫");
		set("value", 100);
		set("material", "cloth");
		set("armor_prop/armor", 3);
	}
	setup();
}
