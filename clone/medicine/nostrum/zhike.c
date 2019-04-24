// zhike.c 止咳药

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY "止咳药" NOR, ({"zhike yao", "zhikeyao", "yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "包");
		set("long", "这是一包常见的止咳药。\n");
		set("value", 2000);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();
	if (!id(arg))
		return 0;
	if (me->is_busy())
		return notify_fail("别急，慢慢来。\n");
	if (!me->query_condition("ill_kesou"))
	{
		write("你现在又没有咳嗽，别乱吃药。\n");
		return 1;
	}
	else
	{
		me->clear_condition("ill_kesou");
		message_vision("$N服下一包止咳药，咳嗽好多了。\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}
