// heye.c 荷叶

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "荷叶" NOR, ({"heye"}));
	set_weight(500);
	set("vegetable", 4);
	set("value", 5);
	set("nostrum", 2);
	set("unit", "片");
	set("long", "这是一片碧绿的荷叶，看来可以入药。\n");
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

	write("吃荷叶？你不会饿到吃叶子的水平吧？\n");
	return 1;
}
