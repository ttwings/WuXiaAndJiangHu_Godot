// sahuaao.c 桃花撒花袄

#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
	set_name(RED "桃花撒花袄" NOR, ({"sahua ao", "cloth"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "件");
		set("value", 1000);
		set("armor_prop/armor", 1);
		set("material", "cloth");
		set("female_only", 1);
	}
	setup();
}
