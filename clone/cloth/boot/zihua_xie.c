// zihua_xie.c

#include <ansi.h>
#include <armor.h>
inherit BOOTS;
void create()
{
	set_name(MAG "Ï¸Ëé×Ï»¨Ð¬" NOR, ({"zihua xie", "xie", "shoes"}));
	set_weight(1000);
	if ( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Ë«");
		set("value", 600);
		set("material", "silk");
		set("armor_prop/armor", 1);
		set("female_only", 1);
		set("armor_prop/personility", 3);
	}
	setup();
}
