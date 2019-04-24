// sangye.c 桑叶

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "桑叶" NOR, ({"sangye"}));
	set_weight(500);
	set("vegetable", 8);
	set("value", 15);
	set("nostrum", 64);
	set("unit", "片");
	set("long", "这是一片烤干的桑叶，看来可以入药。\n");
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

	write("你既不是吐丝的蚕，也不是吃草的兔子，怎么对这有兴趣？\n");
	return 1;
}
