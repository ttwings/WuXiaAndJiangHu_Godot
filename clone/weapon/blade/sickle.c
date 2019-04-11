// sickle.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
	 set_name("镰刀", ({ "sickle", "dao", "blade", "lian", "lian dao" }) );
	 set_weight(1500);
	 if( clonep() )
		 set_default_object(__FILE__);
	 else {
		 set("unit", "柄");
		 set("value", 200);
		 set("material", "wood");
		 set("long", "这是一柄农村中常见的镰刀。\n");
		 set("wield_msg", "$N抽出一把$n握在手中，刀刃上还带着稻草。\n");
		 set("unequip_msg", "$N将手中的$n别回腰带里。\n");
	 }
	 init_blade(5);
	 setup();
}
