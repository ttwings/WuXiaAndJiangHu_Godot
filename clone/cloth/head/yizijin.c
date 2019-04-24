// yizijin.c

#include <armor.h>
inherit HEAD;
void create()
{
	set_name("Ò»×Ö½í", ({"yizi jin", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¿é");
		set("value", 150);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
