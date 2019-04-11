// huxin.c
// Last Modified by winder on May. 29 2001

#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
	set_name( "护心", ({ "hu xin", "huxin" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
		set("long", "这是一件铁质的护心，用以保护心部。\n");
		set("value", 6000);
		set("material", "wrists");
		set("armor_prop/armor", 5);
		set("shaolin",1);
	}
	setup();
}
