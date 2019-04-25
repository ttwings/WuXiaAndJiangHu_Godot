// hook.c 钢钩

#include <weapon.h>
inherit HOOK;

void create()
{
	set_name("钢钩", ({"gang gou", "gou"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄特殊的精钢剑，剑端带着一个倒钩。\n");
		set("value", 100);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回鞘中。\n");
	}
	init_hook(25);
	setup();
}
