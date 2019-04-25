// longpao.c
// Last Modified by winder on May. 25 2001

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(HIY "蟒龙袍" NOR, ({"manglong pao", "cloth", "pao"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "件");
		set("long", "这是一件华贵无比的蟒龙袍。你不由得想穿上它过过皇帝瘾。\n");
		set("value", 15000);
		set("material", "cloth");
		set("armor_prop/armor", 15);
	}
	setup();
}
