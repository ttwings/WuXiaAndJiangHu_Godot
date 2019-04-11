// zaoshahuajin.c

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
	set_name("ÔíÉ´×ª½Ç´Ø»¨½í", ({ "zaosha huajin", "head" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¿é");
		set("value",800);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
