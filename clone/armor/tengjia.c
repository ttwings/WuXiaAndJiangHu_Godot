// tengjia.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit ARMOR;

void create()
{
	set_name("ÌÙ¼×", ({"teng jia","tengjia","jia","armor"}));
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¼ş");
		set("long", "Ò»¼şÇá±ãÌÙ¼×¡£\n");
		set("value", 1500);
		set("material", "wood");
		set("armor_prop/armor", 25);
		}
	setup();
}
