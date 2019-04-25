// moyao.c 没药

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "没药" NOR, ({"moyao"}));
	set_weight(500);
	set("vegetable", 8);
	set("value", 300);
	set("nostrum", 8);
	set("unit", "根");
	set("long", "这是一根名贵药材-没药，看来可以入药。\n");
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

	write("你三口两口把没药吃了下去。\n");
	destruct(this_object());
	return 1;
}
