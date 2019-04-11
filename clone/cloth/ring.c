// ring.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit FINGER;

void create()
{
	set_name("½äÖ¸", ({ "ring", "jie zhi" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¸ö");
		set("material", "gold");
		set("value", 100);
		set("armor_prop/armor", 2);
	}
	setup();
}

