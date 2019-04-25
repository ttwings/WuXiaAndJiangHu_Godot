// head.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit HEAD;

void create()
{
	set_name("头盔", ({"head"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "iron");
		set("unit", "个");
		set("armor_prop/armor", 1);
	}
	setup();
}
