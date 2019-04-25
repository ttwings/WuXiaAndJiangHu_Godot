// yuzhan.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(WHT "玉盏" NOR, ({"yu zhan", "zhan"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "小小的玉质酒盅。\n");
		set("unit", "个");
		set("value", 10000);
		set("max_liquid", 20);
	}
}
