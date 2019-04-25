// wanzijin.c

#include <armor.h>
inherit HEAD;
void create()
{
	set_name("万字巾", ({"wanzi jin", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "块");
		set("value", 300);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
