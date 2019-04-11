// bayuban.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
	 set_name("白玉板", ({ "baiyu ban", "baiyuban", "yuban", "ban" }) );
	 set_weight(1000);
	 if( clonep() )
		 set_default_object(__FILE__);
	 else {
		 set("unit", "块");
		 set("value", 10000);
		 set("material", "wood");
		 set("long", "一块白玉制就的板子，沉甸甸地甚是压手。\n");
		 set("wield_msg", "$N拿起一块$n拍了拍掌心。\n");
		 set("unwield_msg", "$N将$n插回腰间。\n");
	 }
	 init_hammer(15);
	 setup();
}
