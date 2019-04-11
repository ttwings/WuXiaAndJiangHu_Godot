// shexiang.c 麝香

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIB"麝香"NOR, ({"shexiang"}));
	set_weight(500);
	set("vegetable", 16);
	set("value", 1600);
	set("nostrum", 8);
	set("unit", "块");
	set("long", "这是一块香气馥郁的麝香，看来可以入药。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	write("麝香没这种吃法。\n");
	return 1;
}
