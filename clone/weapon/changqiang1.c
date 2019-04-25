// changqiang.c 长枪

#include <weapon.h>
inherit SPEAR;

void create()
{
	set_name("长枪", ({"chang qiang", "qiang", "changqiang"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "杆");
		set("long", "这是一杆比武专用的的精钢长枪,威力非比寻常.\n");
		set("value", 0);
		set("material", "iron");
		set("long", "一杆长枪。\n");
		set("wield_msg", "$N抄起一杆$n，顺手抖了个枪花。\n");
		set("unwield_msg", "$N哼了一声，将$n插回后腰。\n");
	}
	init_spear(100);
	setup();
}
