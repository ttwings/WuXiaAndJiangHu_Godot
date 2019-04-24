// shuozhuo.c 手镯

#include <armor.h>
#include <ansi.h>

inherit WRISTS;

void create()
{
	set_name(HIG "手镯" NOR, ({"shou zhuo", "zhuo"}));
	set("long", "这是一对玉镯，莹滑温润，光洁无瑕，真是稀世罕有。\n");
	set("weight", 300);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "对");
		set("value", 50000);
		set("material", "玉");
		set("armor_prop/armor", 2);
		set("female_only", 1);
	}
	setup();
}
