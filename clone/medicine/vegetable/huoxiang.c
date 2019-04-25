// huoxiang.c 藿香

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(YEL "藿香" NOR, ({"huoxiang"}));
	set_weight(500);
	set("vegetable", 4);
	set("value", 100);
	set("nostrum", 8);
	set("unit", "块");
	set("long", "这是一块刚挖取的藿香，看来可以入药。\n");
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

	write("藿香不能生吃。\n");
	return 1;
}
