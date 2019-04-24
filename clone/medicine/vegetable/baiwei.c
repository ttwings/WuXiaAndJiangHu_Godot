// baiwei.c 白薇

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "白薇" NOR, ({"baiwei"}));
	set_weight(500);
	set("unit", "朵");
	set("value", 1200);
	set("vegetable", 1);
	set("nostrum", 2);
	set("long", "这是一朵盛开的白薇，看来可以入药。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	write("你一口就把白薇吃了下去。\n");
	destruct(this_object());
	return 1;
}
