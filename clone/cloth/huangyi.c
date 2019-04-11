// huangyi.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(HIY"»ÆÉ«Ð¡¹Ó"NOR, ({"huang gua", "yellow cloth", "cloth"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "¼þ");
		set("value", 100);
		set("armor_prop/armor", 5);
	}
	setup();
}

