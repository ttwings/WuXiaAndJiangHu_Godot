// yangjing.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIG "养精丹" NOR, ({"yangjing dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set_weight(4000);
		set("unit", "粒");
		set("vegetable", 7);
		set("nostrum", 128);
		set("level", 10);
		set("value", 5000);
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

	message_vision("$N吃下一粒" + name() + "。\n", me);
	/*	if (((int)me->query_condition("xx_poison") > 0) ||
		((int)me->query("eff_jing") < (int)me->query("max_jing")))
	{
		me->apply_condition("jing_curing", me->query_condition("jing_curing") + 10);
*/
	if (((int)me->query_condition("xx_poison") > 0) ||
		((me->query("eff_jing") / me->query("max_jing")) < 0.9))
	{
		me->receive_curing("jing", (int)me->query("max_jing") / 50);
	}
	me->start_busy(2);
	destruct(this_object());
	return 1;
}
