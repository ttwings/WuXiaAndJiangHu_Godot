// cutang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;
inherit F_LIQUID;

void create()
{
	set_name("醋坛子", ({"tanzi"}));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一个装醋的大坛子．\n");
		set("unit", "个");
		set("value", 50);
		set("max_liquid", 5);
		set("wield_msg", "$N抓起一个$n，握在手中当武器。\n");
		set("material", "bone");
	}

	set("liquid", ([
		"type": "water",
		"name": "香醋",
		"remaining": 5,
	]) );
	init_hammer(5);
	setup();

}

