// baizhi.c 白芷

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "白芷" NOR, ({"baizhi"}));
	set_weight(500);
	set("unit", "朵");
	set("value", 900);
	set("vegetable", 1);
	set("nostrum", 4);
	set("long", "这是一朵盛开的白芷，看来可以入药。\n");
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

	write("你一口就把白芷吃了下去。\n");
	destruct(this_object());
	return 1;
}
