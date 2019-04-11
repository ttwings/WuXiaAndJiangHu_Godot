// gujia.c
// Last Modified by winder on May. 25 2001

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("ÊÞ¹Ç¼×", ({"shougu jia","shougujia","jia","armor"}));
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¼þ");
	set("long", "Ò»¼þÊÞ¹Ç¼×¡£\n");
		set("value", 2500);
		set("material", "bone");
		set("armor_prop/armor", 35);
		}
	setup();
}
