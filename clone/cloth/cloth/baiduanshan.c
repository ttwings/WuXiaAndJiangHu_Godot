// baiduanshan.c  白缎衫

#include <armor.h>
inherit CLOTH;
void create()
{
	set_name("白缎衫", ({"baiduan shan", "cloth"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一套白色的绸衫，柔软飘逸。\n");
		set("unit", "套");
		set("value", 800);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 2);
	}
	setup();
}
