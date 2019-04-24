// qingshajin.c

#include <armor.h>
#include <ansi.h>
inherit HEAD;
void create()
{
	set_name(GRN "ÇàÉ´×¥½ÇÍ·½í" NOR, ({"qingsha jin", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¿é");
		set("value", 600);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
