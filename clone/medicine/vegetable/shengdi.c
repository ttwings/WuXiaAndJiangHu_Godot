// shengdi.c 生地

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(BLK "生地" NOR, ({"shengdi"}));
	set_weight(500);
	set("vegetable", 16);
	set("value", 500);
	set("nostrum", 4);
	set("unit", "块");
	set("long", "这是一块不起眼的生地，看来可以入药。\n");
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

	write("生地你也吃？佩服佩服！\n");
	return 1;
}
