// gouzhizi.c 枸枳子

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIR "枸枳子" NOR, ({"gouzhizi"}));
	set_weight(500);
	set("vegetable", 2);
	set("value", 30);
	set("nostrum", 32);
	set("unit", "粒");
	set("long", "这是一粒陈年的枸枳子，看来可以入药。\n");
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

	write("枸枳子入药才能吃。\n");
	return 1;
}
