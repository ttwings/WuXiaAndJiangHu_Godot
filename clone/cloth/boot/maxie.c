// maxie.c  ÂéĞ¬

#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("ÂéĞ¬", ({"ma xie", "xie", "shoes"}));
	set_weight(1000);
	if ( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "Ò»Ë«ÂéÉş±àÖÆµÄĞ¬×Ó¡£\n");
		set("unit", "Ë«");
		set("value", 5);
		set("material", "silk");
		set("armor_prop/armor", 1);
	}
	setup();
}


