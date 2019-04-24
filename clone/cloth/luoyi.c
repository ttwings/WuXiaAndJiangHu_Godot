// luoyi.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("渌水罗衣", ({"luo yi", "fancy skirt", "skirt"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "件");
		set("long", "这是件看起来非常典雅的长裙，却不知是什么制成。\n");
		set("value", 1500);
		set("material", "cloth");
		set("armor_prop/armor", 10);
		set("armor_prop/dodge", 10);
		set("armor_prop/personality", 3);
		set("female_only", 1);
	}
	setup();
}
