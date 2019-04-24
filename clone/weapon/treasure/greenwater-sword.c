// greenwater-sword.c 碧水剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIG "碧水剑" NOR, ({"greenwater sword", "jian", "sword"}));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "这是一把通体晶莹剔透的剑!\n");
		set("value", 400);
		set("material", "crimsonsteel");
		set("wield_msg", "$N「唰」地一声抽出一把$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插入腰间的剑鞘。\n");
	}
	init_sword(100);
	setup();
}
