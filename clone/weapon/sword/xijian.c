// xijian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("细剑", ({ "xi jian", "jian", "sword" }) );
	set_weight(1400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 700);
		set("material", "steel");
		set("long", "这是一把又细又长的剑，轻飘飘的像是女孩子家的玩意。但衡山一派上下都用此细剑。\n");
		set("wield_msg", "$N抽出一把剑身细长的剑，握在手中。\n");
		set("unequip_msg", "$N放下手中的$n。\n");
		set("weapon_prop/courage", -4);
	}
	init_sword(16);
	setup();
}
