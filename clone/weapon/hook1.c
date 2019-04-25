// gou1.c 长剑

#include <weapon.h>
inherit HOOK;

void create()
{
	set_name("钢钩", ({"gang gou", "gou", "hook"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄比武专用的的精钢钢钩,威力非比寻常.\n");
		set("value", 0);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回鞘中。\n");
	}
	init_hook(100);
	setup();
}
