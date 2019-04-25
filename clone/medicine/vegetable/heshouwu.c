// heshouwu.c 何首乌

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(WHT "何首乌" NOR, ({"heshouwu"}));
	set_weight(800);
	set("vegetable", 4);
	set("nostrum", 1);
	set("unit", "支");
	set("long", "这是一支已成人形的何首乌，看来可以入药。\n");
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

	if ((int)me->query("max_jingli") <= 200)
	{
		write("你吃下了一支何首乌，只觉得精神健旺之极。\n");
		me->add("max_jingli", 2);
		me->add("jingli", 2);
	}
	else
	{
		write("你吃下了一支何首乌，但是好象没什么用。\n");
	}
	me->unconcious();
	destruct(this_object());
	return 1;
}
