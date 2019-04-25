// huafu.c
// Last Modified by winder on May. 25 2001

#include <ansi.h>
#include <weapon.h>
inherit AXE;

void create()
{
	set_name("宣花斧", ({"xuanhua fu", "fu", "axe"}));
	set_weight(12000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "这是把沉重的大斧，有八尺多长，锋利无比。\n");
		set("value", 5000);
		set("material", "iron");
		set("wield_msg", "$N拿出一把$n握在手中，眼前闪过一道寒光。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
	}
	init_axe(60);
	setup();
}
