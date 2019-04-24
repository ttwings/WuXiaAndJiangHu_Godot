// jiasha.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>
inherit CLOTH;
inherit F_UNIQUE;

void create()
{
	set_name(HIY "½õïçôÂôÄ" NOR, ({"jinlan jiasha", "jiasha", "cloth"}));
	set("long", "Ò»¼şÉ«²Ê°ßìµµÄ½õìµôÂôÄ¡£\n");
	set_weight(3000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¼ş");
		set("material", "cloth");
		set("armor_prop/armor", 90);
		set("armor_prop/dodge", 20);
		set("value", 50000);
	}
	setup();
}
