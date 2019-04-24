// yuruyi.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "玉如意" NOR, ({"yu ruyi", "ruyi"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "玉如意。\n");
		set("unit", "个");
		set("value", 200000);
	}
}
