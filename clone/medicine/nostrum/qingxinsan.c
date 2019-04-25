// qingxinsan.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("清心散", ({"qingxin san", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一包星宿派的清心散，专为星宿解毒之用。\n");
		set("vegetable", 9);
		set("nostrum", 35);
		set("level", 20);
		set("unit", "包");
		set("value", 1000);
	}
	set("pour_type", "1");
	setup();
}

int init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
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

	message_vision("$N吃下一包" + name() + "。\n", me);
	if ((int)me->query_condition("xx_poison") > 0)
	{
		me->apply_condition("xx_poison", 0);
	}

	destruct(this_object());
	return 1;
}
