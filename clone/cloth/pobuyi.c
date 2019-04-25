// pobuyi.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("破布衣", ({"po buyi", "buyi", "cloth"}));
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一件破烂不堪的布衣，也不知多少年没洗过了，上面满是窟窿。\n");
		set("material", "cloth");
		set("unit", "件");
		set("value", 0);
		set("armor_prop/armor", 1);
	}
	setup();
}
