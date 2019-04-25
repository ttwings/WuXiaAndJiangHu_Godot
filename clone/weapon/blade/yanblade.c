// yanblade.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

void create()
{
	set_name("雁云刀", ({"yanyun blade", "blade"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("long", "一把白灿灿的挽手胡刀，发着阴渗渗的杀气．\n");
		set("value", 1500);
		set("material", "crimsonsteel");
		set("wield_msg", "$N「唰」地一声抽出一把$n握在手中，脸色更加阴沉了！\n");
		set("unwield_msg", "$N将手中的$n插入腰间，嘴角露出一丝笑意。\n");
		set("weapon_prop/courage", 10);
	}
	init_blade(40);
	setup();
}
