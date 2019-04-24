// Pill: bicanfeng.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(GRN "碧蚕粉" NOR, ({"bican fen", "fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一袋剧毒的毒药, 如果用来炼暗器有见血封喉之效. \n");
		set("unit", "袋");
		set("value", 20000);
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

	message_vision("$N仰头把一小袋" + name() + "都咽了下去。\n", me);
	me->set_temp("die_reason", "服下碧蚕粉，自杀身亡了");
	me->die();
	destruct(this_object());
	return 1;
}
