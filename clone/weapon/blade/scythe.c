// scythe.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
	 set_name("长柄镰刀", ({ "scythe","blade","dao","lian dao","lian"}) );
	 set_weight(2000);
	 if( clonep() )
		 set_default_object(__FILE__);
	 else {
		 set("unit", "柄");
		 set("value", 300);
		 set("material", "wood");
		 set("long", "这是一柄农民惯用的长柄镰刀。\n");
		 set("wield_msg", "$N抽出一把$n握在手中，刀刃上还挂着稻草。\n");
		 set("unwield_msg", "$N将手中的$n别回腰带中。\n");
	 }
	 init_blade(10, TWO_HANDED);
	 setup();
}
