//langyamace.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
	set_name("狼牙棒", ({"langya bang", "mace", "langyabang", "langya"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 18000);
		set("material", "iron");
		set("long", "乌黑的狼牙棒上生满了倒刺，让人不由得凛然生畏。\n");
		set("wield_msg", "$N“呼”的一声抽出一柄$n，恶狠狠地盯着周围的人！\n");
		set("unwield_msg", "$N小心翼翼地收起$n，差点被倒刺伤着自己。\n");
	}

	init_mace(35);
	setup();
}
