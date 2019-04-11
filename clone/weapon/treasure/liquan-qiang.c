// liquan-qiang.c 沥泉枪
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SPEAR;
inherit F_UNIQUE;

void create()
{
	set_name(HIW"沥泉枪"NOR,({"liquan spear", "spear", "qiang"}));
	set_weight(100000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "杆");
		set("long","这是武穆遗物。当年岳武穆捻灵蛇而得神兵，百战功成，多赖此枪。\n");
		set("material", "steel");
		set("no_drop", 1);
		set("value", 100);
		set("wield_msg", "$N「唰」的一声提起一根$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n收回背后。\n");
	}
	init_spear(200);
	setup();
}
