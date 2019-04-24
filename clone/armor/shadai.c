// shadai.c
// Last Modified by winder on May. 29 2001

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("沙袋", ({"sha dai", "shadai"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "副");
		set("long", "这是一副沙袋，里面装满了铁砂，用以练习轻功。\n");
		set("value", 6000);
		set("material", "wrists");
		set("armor_prop/armor", 5);
		set("shaolin", 1);
		set("wear_msg", YEL "$N拿出一副沙袋绑在腿上。\n" NOR);
		set("remove_msg", YEL "$N把沙袋从腿上取了下来。\n" NOR);
	}
	setup();
}
