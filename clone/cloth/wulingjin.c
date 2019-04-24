// wulingjin.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit HEAD;

void create()
{
	set_name("乌绫巾", ({"wuling jin", "jin"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "顶");
		set("long", "一顶黑缎子制成的丝带，用来束发。\n");
		set("value", 300);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 1);
	}
	setup();
}
