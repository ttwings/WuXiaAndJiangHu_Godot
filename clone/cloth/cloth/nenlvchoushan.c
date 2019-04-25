// nenlvchoushan.c 嫩绿绸衫

#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
	set_name(GRN "嫩绿绸衫" NOR, ({"nenlv choushan", "cloth"}));
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
