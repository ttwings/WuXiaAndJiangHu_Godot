// gangzhang
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STAFF;

void create()
{
	set_name("钢杖", ({"gang zhang", "zhang", "staff"}));
	set_weight(6000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 300);
		set("material", "steel");
		set("long", "这是一钢制的杖．\n");
		set("wield_msg", "$N抽出一把$n握在手中。\n");
		set("unequip_msg", "$N将手中的$n插入腰后．\n");
	}
	init_staff(35);
	setup();
}

