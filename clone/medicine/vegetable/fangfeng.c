// fangfeng.c 防风

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY"防风"NOR, ({"fangfeng"}));
	set_weight(500);
	set("vegetable", 2);
	set("value", 200);
	set("nostrum", 4);
	set("unit", "块");
	set("long", "这是一块保存好久的防风，看来可以入药。\n");
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

	write("防风入药才能吃的。\n");
	return 1;
}
