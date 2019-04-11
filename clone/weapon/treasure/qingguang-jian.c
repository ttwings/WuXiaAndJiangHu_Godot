// qingguang-jian.c 青光剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIC"青光剑"NOR, ({ "qingguang jian", "jian", "sword" }) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long",HIC"这把剑长约四尺，青光闪闪，的确是把利器。\n"NOR);
		set("value", 10000);
		set("material", "steel");
	}
	init_sword(120);
	set("no_drop", "这样东西不能离开你。\n");
	set("no_put","如此宝剑如何能乱放？\n");
	set("wield_msg", "只听见「飕」地一声，$N的手中已经多了一把青光四射寒气逼人的利剑——$n。\n");
	set("unequip_msg", "$N将手中的$n插入腰间的剑鞘。\n");
	setup();
}
