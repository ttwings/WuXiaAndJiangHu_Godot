// maoeryan.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(GRN "猫儿眼" NOR, ({"maoer yan", "yan"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一粒暗绿而发放毫光的宝石。\n");
		set("unit", "粒");
		set("value", 100000);
	}
}
