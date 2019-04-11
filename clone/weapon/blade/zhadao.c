// zhadao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("铡刀", ({ "zhadao", "blade", "dao" }) );
	set_weight(3500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一把用来铡草，砍小树枝的铡刀。\n");
		set("unit", "把");
		set("wield_msg", "$N抽出一柄$n横握在手中，到也威风凛凛。\n");
		set("unwield_msg", "$N放下手中$n，难到要立地成佛？\n");
		set("value", 400);
		set("material","wood");
	}
	init_blade(20);
	setup();
}

