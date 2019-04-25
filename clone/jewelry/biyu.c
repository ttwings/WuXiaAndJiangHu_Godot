// biyu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "碧玉" NOR, ({"bi yu", "yu"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一块碧绿如缎的玉。\n");
		set("unit", "块");
		set("value", 80000);
	}
}
