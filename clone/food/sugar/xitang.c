// xitang.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIR "喜糖" NOR, ({"xi tang", "tang"}));
	set("unit", "包");
	set("value", 10000);
	set("long", "这是一包「侠客行一百」飞雪堂特制的精美喜糖。\n");
	set("amount", 100);
	setup();
}

int do_eat(string arg)
{
	object me = this_player();
	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (arg == "xi tang" || arg == "tang")
	{
		message_vision(NOR "$N把一包" HIR "喜糖" NOR "吃个精光，分享了新郎新娘的甜蜜与温馨。\n", me);

		destruct(this_object());
	}
	return 1;
}
