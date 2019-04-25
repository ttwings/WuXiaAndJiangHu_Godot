// tianqi.c 田七

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY "田七" NOR, ({"tianqi"}));
	set_weight(800);
	set("vegetable", 16);
	set("value", 550);
	set("nostrum", 32);
	set("unit", "根");
	set("long", "这是一根田七，看来可以入药。\n");
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

	write("你三口两口把田七吃了下去。\n");
	destruct(this_object());
	return 1;
}
