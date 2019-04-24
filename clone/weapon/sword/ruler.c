// ruler.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("戒尺", ({"ruler"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "一把黑黝黝的戒尺．\n");
		set("value", 80);
		set("material", "wood");
		set("wield_msg", "$N「唰」地一声抽出一把$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插入腰间。\n");
	}
	init_sword(10);
	setup();
}
