// armor.c
// Last Modified by winder on May. 25 2001

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("îø¼×", ({"armor"}));
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "iron");
		set("unit", "¸±");
		set("armor_prop/armor", 5);
	}
	setup();
}
