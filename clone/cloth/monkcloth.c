// monkcloth.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIY"»¤·¨ôÂôÄ"NOR, ({ "hufa jiasha", "jiasha", "cloth" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "¼þ");
		set("armor_prop/armor", 15);
	}
	setup();
}

