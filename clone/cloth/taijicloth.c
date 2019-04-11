// taijicloth.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("太极道袍", ({"taiji daopao", "cloth", "pao"}));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
"一件道士穿的长袍，中有太极八卦，左右绣有日月乾坤．\n");
		set("unit", "件");
		set("value", 500);
		set("material", "cloth");
		set("armor_prop/armor", 4);
		set("armor_prop/spells", 5);
	}
}

