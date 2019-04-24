// axe1.c 长剑

#include <weapon.h>
inherit AXE;

void create()
{
	set_name("板斧", ({"ban fu", "axe", "fu"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄沉重的板斧。\n");
		set("value", 0);
		set("material", "steel");
		set("wield_msg", "$N「忽」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回腰后。\n");
	}
	init_axe(100);
	setup();
}
