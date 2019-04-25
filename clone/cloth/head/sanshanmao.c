// sanshanmao.c

#include <armor.h>
inherit HEAD;
void create()
{
	set_name("三山帽", ({"sanshan mao", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "顶");
		set("value", 400);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
