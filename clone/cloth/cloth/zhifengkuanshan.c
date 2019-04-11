// zhifeng_huanshan.c 直缝宽衫

#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("直缝宽衫", ({ "zhifeng kuanshan", "cloth" }));
	set("long","一套宽大柔软的布衫，穿上想必很舒适。\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "套");
		set("value", 700);
		set("armor_prop/armor", 1);
	}
	setup();
}
