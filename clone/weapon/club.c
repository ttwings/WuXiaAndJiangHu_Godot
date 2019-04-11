// mugun.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit CLUB;

void create()
{
	set_name("木棍", ({"mugun"}));
	set_weight(1400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "根");
		set("value", 100);
		set("material", "wood");
		set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");
	}
	init_club(15);
	setup();
}

