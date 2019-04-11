// yupei.c 玉佩

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
	set_name(HIC"玉佩"NOR, ({ "yu pei", "yu" }));
	set("long", "这是一块淡兰色的宝玉，莹滑温润，光洁无瑕，真是稀世罕有。\n");
	set("weight", 300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("value", 50000);
		set("material", "玉");
		set("armor_prop/armor", 2);
		set("female_only", 1);
	}
	setup();
}	

