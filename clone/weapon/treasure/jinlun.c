// jinlun.c 金轮
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;
inherit F_UNIQUE;

void create()
{
	set_name( HIY "金轮" NOR,({ "jin lun" ,"lun" ,"jinlun" }));
	set_weight(100000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long",HIY"这是一柄金光闪闪的法轮。\n"NOR);
		set("value", 10000);
		set("material", "gold");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg","$N将手中的$n放回腰间。\n");
	}
	init_hammer(150);
	setup();
}
