// shabu_zhizhui.c 纱布直缀

#include <armor.h>
inherit CLOTH;

void create()
{
	set_name("纱布直缀", ({"shabu zhizhui", "cloth"}));
	set_weight(1500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一套黑纱布的对襟衣服，常见和尚行者穿著。\n");
		set("unit", "套");
		set("value", 300);
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}
