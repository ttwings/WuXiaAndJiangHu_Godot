// baizhusipao.c 白苎丝袍

#include <armor.h>
inherit CLOTH;
void create()
{
	set_name("白苎丝袍", ({"baisi pao", "cloth"}));
	set("long", "一套玉色的苎丝袍，裁剪和体，缝制精细。\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "cloth");
		set("unit", "套");
		set("value", 1000);
		set("armor_prop/armor", 2);
		set("armor_prop/personality", 2);
	}
	setup();
}
