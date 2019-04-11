// hufa-jiasha.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIY"护法袈裟"NOR, ({ "hufa jiasha", "jiasha", "cloth" }) );
	set("long","一件金光灿灿的护法袈裟。");
	set_weight(4000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("value", 2000);
		set("material", "cloth");
		set("armor_prop/armor", 20);
	}
	setup();
}

