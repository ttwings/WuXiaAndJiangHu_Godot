// yujie.c

#include <ansi.h>
#include <armor.h>

inherit FINGER;

void create()
{
	set_name(CYN"Óñ½äÖ¸"NOR, ({"yu jiezhi", "jiezhi", "finger"}));
	set_weight(500);
	if ( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "°×Óñµñ³ÉµÄ½äÖ¸£¬Ó¨°×Ô²Èó\n");
		set("unit", "Ã¶");
                set("value", 30000);
		set("material", "jade");
                set("armor_prop/armor", 3);
	}
	setup();
}

