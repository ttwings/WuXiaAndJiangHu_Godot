// hei.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("黑袍", ({"hei pao", "black cloth", "cloth"}));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("long", "一件黑色的布袍，一丝杂色也没有．\n");
		set("unit", "件");
		set("value", 200);
		set("armor_prop/armor", 5);
	}
	setup();
}

