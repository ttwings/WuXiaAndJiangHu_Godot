// finger.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit FINGER;

void create()
{
	set_name("Ö¸Ì×", ({"finger"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "iron");
		set("unit", "Ì×");
		set("armor_prop/armor", 1);
	}
	setup();
}

