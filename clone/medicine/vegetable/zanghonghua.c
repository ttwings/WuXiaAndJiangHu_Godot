// zanghonghua.c 藏红花

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIR "藏红花" NOR, ({"zanghonghua"}));
	set_weight(500);
	set("vegetable", 32);
	set("value", 1700);
	set("nostrum", 8);
	set("unit", "朵");
	set("long", "这是一朵来自雪域高原的藏红花，看来可以入药。\n");
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

	write("记得韦爵爷说过：战马吃了芍药花，能全身活血。你吃藏红花图个啥呦！\n");
	return 1;
}
