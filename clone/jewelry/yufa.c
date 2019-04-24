// yufa.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(CYN "玉发簪" NOR, ({"yu fazan", "fazan"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "白玉雕成的发簪，纹理清晰，圆滑光泽。\n");
		set("unit", "枚");
		set("value", 50000);
		set("material", "gold");
		set("armor_prop/armor", 5);
		set("female_only", 1);
	}
	setup();
}
