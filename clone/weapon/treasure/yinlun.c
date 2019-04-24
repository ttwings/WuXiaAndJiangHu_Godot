// yinlun.c 银轮
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;
inherit F_UNIQUE;

void create()
{
	set_name(HIW "银轮" NOR, ({"yin lun", "lun", "yinlun"}));
	set_weight(70000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", HIW "这是一柄银光闪闪的法轮。\n" NOR);
		set("value", 10000);
		set("material", "silver");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n放回腰间。\n");
	}
	init_hammer(100);
	setup();
}
