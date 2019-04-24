// kuojian.c 阔剑

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("阔剑", ({"wide sword", "sword", "jian"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄嵩山弟子常用的的阔剑。\n");
		set("value", 300);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(30);
	setup();
}
