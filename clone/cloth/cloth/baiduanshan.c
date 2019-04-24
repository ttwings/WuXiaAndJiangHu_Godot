// baiduanshan.c  °×¶ĞÉÀ

#include <armor.h>
inherit CLOTH;
void create()
{
	set_name("°×¶ĞÉÀ", ({"baiduan shan", "cloth"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "Ò»Ì×°×É«µÄ³ñÉÀ£¬ÈáÈíÆ®Òİ¡£\n");
		set("unit", "Ì×");
		set("value", 800);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 2);
	}
	setup();
}
