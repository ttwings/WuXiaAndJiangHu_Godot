// sanshanmao.c

#include <armor.h>
inherit HEAD;
void create()
{
	set_name("ÈýÉ½Ã±", ({"sanshan mao", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¶¥");
		set("value", 400);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
