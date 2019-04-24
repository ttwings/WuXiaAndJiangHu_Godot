// pickaxe.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit AXE;

void create()
{
	set_name("锄头", ({"pickaxe", "axe", "chutou", "chu"}));
	set_weight(20000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "一把沉重的锄头，看上去很结实。\n");
		set("value", 2000);
		set("wield_msg", "$N拿出一把$n，一个没拿稳，差点砸在自己脚上。\n");
		set("unwield_msg", "$N放下手中的$n，气喘吁吁地擦了擦汗。\n");
	}
	init_axe(20, TWO_HANDED);
	setup();
}
