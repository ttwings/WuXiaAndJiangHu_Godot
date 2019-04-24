// nuanmao.c

#include <armor.h>
inherit HEAD;
void create()
{
	set_name("ÕÚ³¾Å¯Ã±", ({"nuan mao", "head"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "¶¥");
		set("value", 150);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
