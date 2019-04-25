// gangdao1.c

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("钢刀", ({"blade", "dao"}));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄比武专用的钢刀,威力非比寻常。\n");
		set("value", 0);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回刀鞘。\n");
	}
	init_blade(100);
	setup();
}
