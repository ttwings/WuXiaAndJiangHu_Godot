// ylbian.c 云龙鞭

#include <ansi.h>
#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;

void create()
{
	set_name(HIC "云龙鞭" NOR, ({"yunlong bian", "bian"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是天地会总舵主陈近南的贴身神兵。\n");
		set("value", 100);
		set("material", "leather");
		set("wield_msg", "$N「唰」的一声抖出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n卷回腰间。\n");
	}
	init_whip(150);
	setup();
}
