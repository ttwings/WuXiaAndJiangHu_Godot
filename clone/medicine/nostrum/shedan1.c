// poison: shedan.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
#include <ansi.h>
int cure_ob(string);

void create()
{
	set_name("毒蛇胆", ({"shedan", "dan"}));
	set("unit", "粒");
	set("long", "这是一只绿莹莹的毒蛇胆。\n");
	set("value", 200);
	set("medicine", 1);
	setup();
}
int do_eat(string arg)
{
	int taoism_limit, jingli_limit;
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ((int)me->query_condition("snake_poison") > 7)
	{
		me->apply_condition("snake_poison", (int)me->query_condition("snake_poison") - 5);
	}
	message_vision("$N吃下一副毒蛇胆，一不小心咬破了，好苦哦。\n", me);
	destruct(this_object());
	return 1;
}
