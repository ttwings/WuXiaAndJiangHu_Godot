// danggui.c 当归

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(YEL"当归"NOR, ({"danggui"}));
	set_weight(500);
	set("vegetable", 2);
	set("value", 300);
	set("nostrum", 2);
	set("unit", "块");
	set("long", "这是一块烘干过的当归，看来可以入药。\n");
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

	write("你三口两口就把当归吃了下去。\n");
	destruct(this_object());
	return 1;
}
