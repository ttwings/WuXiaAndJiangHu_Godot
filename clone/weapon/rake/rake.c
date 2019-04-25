// rake.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit RAKE;

void create()
{
	set_name("钢耙", ({"gang pa", "pa", "rake"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 1000);
		set("material", "iron");
		set("long", "一柄长长的七齿钢耙。\n");
		set("wield_msg", "$N抄起一柄$n，在头上挥舞了一圈。\n");
	}
	init_rake(25);
	setup();
}
