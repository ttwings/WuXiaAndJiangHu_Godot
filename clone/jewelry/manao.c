// manao.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "玛瑙" NOR, ({"ma nao", "manao"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一块晶莹古雅的玛瑙。\n");
		set("unit", "块");
		set("value", 70000);
	}
}
