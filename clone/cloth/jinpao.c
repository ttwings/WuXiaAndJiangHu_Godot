// jinpao.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("锦花袍", ({"jinhua pao","cloth","pao"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long",
"这是一件华贵无比的锦花袍，上面绣着各种花草，还有一股香气．\n");
		set("value", 5000);
		set("material", "cloth");
		set("armor_type", "cloth");
		set("armor_prop/armor", 10);
		set("armor_prop/personality", 3);
	}
	setup();
}

