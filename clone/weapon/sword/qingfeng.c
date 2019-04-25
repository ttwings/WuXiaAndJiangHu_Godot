// qingfeng.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("青锋剑", ({"qingfeng sword", "jian", "sword"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("value", 7000);
		set("material", "steel");
		set("long", "这是一把又细又长的剑，剑身锐利。\n");
		set("wield_msg", "一道青光闪过，$N手中已多了把$n。\n");
		set("unequip_msg", "$N放下手中的$n。\n");
	}
	init_sword(65);
	setup();
}
