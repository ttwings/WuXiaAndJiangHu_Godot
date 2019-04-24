// Last Modified by winder on Apr. 25 2001
// shenliwan.c 神力丸

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "神力丸" NOR, ({"shenli wan", "wan"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一颗园园的神力丸，据说吃了可以增强膂力。\n");
		set("value", 10000);
		set("unit", "颗");
	}
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me;

	if (!id(arg))
		return notify_fail("你要吃什么？\n");

	me = this_player();
	message_vision("$N一仰脖，吞下了一颗" + this_object()->name() +
					   "。\n",
				   me);
	if (me->query("gift/shenliwan") >= 5)
	{
		message_vision("$N眨眨眼。\n", me);
		tell_object(me, "你觉得这药没啥味道，还不如花生好吃。\n");
	}
	else if (random(5) == 0)
	{
		tell_object(me, "不过你觉得好像没什么作用。\n");
	}
	else
	{
		tell_object(me, HIR "你觉得双臂几乎爆裂，充满了力量。\n" NOR);
		me->add_temp("apply/strength", 1);
	}

	me->add("gift/shenliwan", 1);
	destruct(this_object());
	return 1;
}
