// ironaxe.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit AXE;

void create()
{
	 set_name("铁斧", ({ "tiefu", "axe", "fu", "tie fu"}) );
	 set_weight(8000);
	 if( clonep() )
		 set_default_object(__FILE__);
	 else {
		 set("unit", "把");
		 set("long", "这是一把劈柴用的铁斧，砍起东西来非常顺手。\n");
		 set("value", 1000);
		 set("wield_msg", "$N拿出一把砍柴的$n，握在手中当作武器。\n");
		 set("unwield_msg", "$N放下手中的$n。\n");
	 }
	 init_axe(20);
	 setup();
}
