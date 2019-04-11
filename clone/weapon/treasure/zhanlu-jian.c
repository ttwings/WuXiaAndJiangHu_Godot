// zhanlu-jian.c 湛卢剑
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIC"湛卢剑"NOR, ({ "zhanlu jian", "sword", "jian" }));
	set_weight(20000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是春秋名匠欧冶子所铸的五口宝剑之湛卢剑。\n");
		set("value", 100000);
		set("material", "steel");
		set("weapon_prop/personality", 8);
		set("wield_msg", "$N「唰」的一声抽出一口寒光闪闪的$n。剑面浮纹跃然闪动，实是一口难得的神兵。\n");
		set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
	}
	init_sword(180);
	setup();
}
