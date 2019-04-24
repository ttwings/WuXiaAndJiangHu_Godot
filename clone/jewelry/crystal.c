// shoe.c

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

void create()
{
	set_name(HIW "水晶鞋" NOR, ({"crystal shoes", "shoes"}));
	set("long", "这是一双晶鞋。\n");
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "水晶");
		set("unit", "双");
		set("value", 5000);
		set("armor_prop/armor", 3);
		set("armor_prop/personality", 3);
		set("female_only", 1);
	}
	setup();
}
