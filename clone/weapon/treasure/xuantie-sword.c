// xuantie-sword.c 玄铁剑
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIB "玄铁剑" NOR, ({"iron sword", "sword", "jian"}));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "此剑由天上陨铁打就，十分沉重，为天下第二神兵。\n");
		set("material", "steel");
		set("value", 100000);
		set("wield_msg", HIB "一团黑气猛地扑面而来，玄铁剑已握在$N手中。\n" NOR);
		set("unwield_msg", HIB "$N手中玄铁剑一声沉重的暗响插入鞘中。\n" NOR);
	}
	init_sword(250);
	setup();
}

void owner_is_killed()
{
	destruct(this_object());
}
