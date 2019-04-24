// jinlongbian.c 金龙鞭

#include <ansi.h>
#include <weapon.h>
inherit WHIP;
inherit F_UNIQUE;

void create()
{
	set_name(YEL "金龙鞭" NOR, ({"jinlong bian", "bian"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是西域富商大贾尹克西的贴身兵器金龙鞭，\n"
					"它的柄乃纯金打造而成，通身镶满各种宝石。\n");
		set("value", 20000);
		set("material", "leather");
		set("wield_msg", "$N「唰」的一声抖出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n卷回腰间。\n");
	}
	init_whip(150);
	setup();
}
