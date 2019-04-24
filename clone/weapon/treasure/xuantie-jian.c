// xuantie-jian.c 玄铁重剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(WHT "玄铁重剑" NOR, ({"iron sword", "jian", "sword"}));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", WHT @LONG
						这把剑长三尺有余，黑黝黝的，竟有七八十斤重。剑两边剑锋都是钝口，
							剑尖更圆圆的似是个半球。 LONG
								NOR);
		set("value", 100000);
		set("material", "iron");
	}
	init_sword(160);
	set("no_drop", "这样东西不能离开你。\n");
	set("no_put", "如此宝剑如何能乱放？\n");
	set("wield_msg", "只听见「铛」地一巨响，$N拔出了一把黑黝黝的武林重宝——$n。\n");
	set("unequip_msg", "$N将手中的$n插入背上的剑鞘。\n");
	setup();
}
