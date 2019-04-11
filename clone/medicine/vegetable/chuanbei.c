// chuanbei.c 川贝

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(RED"川贝"NOR, ({"chuanbei"}));
	set_weight(500);
	set("vegetable", 1);
	set("value", 500);
	set("nostrum", 64);
	set("unit", "粒");
	set("long", "这是一粒不起眼的川贝，看来可以入药。\n");
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

	write("你三口两口就把川贝吃了下去。\n");
	destruct(this_object());
	return 1;
}
