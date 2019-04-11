// nenlvchoushan.c ÄÛÂÌ³ñÉÀ

#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
	set_name( GRN "ÄÛÂÌ³ñÉÀ" NOR, ({ "nenlv choushan", "cloth" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¼ş");
		set("value", 1000);
		set("armor_prop/armor", 1);
		set("material", "cloth");
		set("female_only", 1);
	}
	setup();
}
