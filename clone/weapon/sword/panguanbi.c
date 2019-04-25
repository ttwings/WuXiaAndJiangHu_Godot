// panguanbi.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
	set_name("判官笔", ({"panguanbi", "sword"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "双");
		set("value", 300);
	}
	init_sword(20);
	setup();
}
