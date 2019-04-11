// sengxie.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit BOOTS;

void create()
{
	set_name( "É®Ð¬", ({ "seng xie", "xie" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Ë«");
		set("long", "Ò»Ë«Ô²¿ÚÇà²¼É®Ð¬¡£");
		set("value", 100);
		set("material", "boots");
		set("armor_prop/dodge", 3);
	}
	setup();
}

