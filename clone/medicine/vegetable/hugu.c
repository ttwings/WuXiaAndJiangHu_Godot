// hugu.c 虎骨

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(YEL "虎骨" NOR, ({"hugu"}));
	set_weight(500);
	set("vegetable", 4);
	set("value", 30000);
	set("nostrum", 4);
	set("unit", "块");
	set("long", "这是一块熬制过的虎骨，看来可以入药。\n");
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

	write("狗才啃骨头。你不是吧？\n");
	return 1;
}
