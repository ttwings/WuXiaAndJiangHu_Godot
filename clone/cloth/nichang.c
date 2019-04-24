// nichang.c 碧水霓裳
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
	set_name(HIG "碧水霓裳" NOR, ({"bishui yingshang", "cloth"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一条薄如蝉翼，幽香沁人的碧色长裙，轻颤颤地不知由什么布料做成。\n");
		set("unit", "条");
		set("value", 8000);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 5);
		set("female_only", 1);
	}
	setup();
}
