// biyuqiang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SPEAR;

void create()
{
	set_name("碧玉双枪", ({"jade spear", "spear"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "杆");
		set("long", "一对玉制的青色短枪，象是有钱人家的摆设，却又锋利无比．\n");
		set("value", 9000);
		set("material", "blacksteel");
		set("wield_msg", "$N双手一分，从背后解下一对短枪握到手中．\n");
		set("unwield_msg", "$N将手中的$n系到背后．\n");
	}
	init_spear(20);
	setup();
}
