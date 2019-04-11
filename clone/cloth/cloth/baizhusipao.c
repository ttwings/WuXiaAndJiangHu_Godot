// baizhusipao.c °×ÜÑË¿ÅÛ

#include <armor.h>
inherit CLOTH;
void create()
{
	set_name("°×ÜÑË¿ÅÛ", ({ "baisi pao", "cloth" }));
	set("long","Ò»Ì×ÓñÉ«µÄÜÑË¿ÅÛ£¬²Ã¼ôºÍÌå£¬·ìÖÆ¾«Ï¸¡£\n");
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "Ì×");
		set("value", 1000);
		set("armor_prop/armor", 2);
		set("armor_prop/personality", 2);
	}
	setup();
}

