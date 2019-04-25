// zihua_xie.c

#include <ansi.h>
#include <armor.h>
inherit BOOTS;
void create()
{
	set_name(MAG "细碎紫花鞋" NOR, ({"zihua xie", "xie", "shoes"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "双");
		set("value", 600);
		set("material", "silk");
		set("armor_prop/armor", 1);
		set("female_only", 1);
		set("armor_prop/personility", 3);
	}
	setup();
}
