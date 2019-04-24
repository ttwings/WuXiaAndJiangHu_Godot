// yubei.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(WHT "玉杯" NOR, ({"yu bei", "bei"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "小小的玉杯。做工精细。\n");
		set("unit", "个");
		set("value", 10000);
		set("max_liquid", 20);
	}
}
