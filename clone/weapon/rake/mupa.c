// mupa.c 
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit RAKE;

void create()
{
	set_name("木耙", ({"mu pa", "pa", "rake"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("value", 100);
		set("material", "wood");
		set("long", "这是一柄长长的木耙，是练武时用的．\n");
		set("wield_msg", "$N抽出一柄$n握在手中。\n");
	}
	init_rake(15);
	setup();
}

