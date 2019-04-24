// duanyun-axe.c 断云斧
// Last Modified by suncity on Feb. 13 2003

#include <ansi.h>
#include <weapon.h>
inherit AXE;
inherit F_UNIQUE;

void create()
{
	set_name(HIW "断云斧" NOR, ({"duanyun fu", "axe", "fu"}));
	set_weight(40000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("value", 10000);
		set("material", "iron");
		set("long", HIW "这是一把银光闪闪的斧头。\n" NOR);
		set("wield_msg", HIW "一道白光，$n已在$N手中，只觉气成风云，声为雷霆。\n" NOR);
		set("unwield_msg", HIW "$N放下手中的$n，华光顿敛，天地间只闻龙鸣。\n" NOR);
	}
	init_axe(250);
	setup();
}
