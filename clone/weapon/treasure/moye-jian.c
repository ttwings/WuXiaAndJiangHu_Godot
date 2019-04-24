// moye.c 莫邪剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(MAG "莫邪剑" NOR, ({"moye jian", "jian", "sword"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这就是赫赫有名的莫邪，剑锋上隐隐透出一股紫气，仔细凝望，只觉一股肃杀之气森然外散。\n");
		set("value", 20000);
		set("material", "steel");
		set("weapon_prop/personality", 8);
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中，顿时只听冤魂惨嚎，令人毛骨悚然。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘，一下子风平浪静，晴空万里。\n");
	}
	init_sword(120);
	setup();
}
