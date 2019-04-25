// zhenzhu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "珍珠" NOR, ({"zhen zhu", "zhu"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一粒龙眼大的珍珠。\n");
		set("unit", "粒");
		set("value", 20000);
	}
}
