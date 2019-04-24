// baihudan.c 白虎夺命丹

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "白虎夺命丹" NOR, ({"baihu duomingdan", "dan"}));
	set("unit", "粒");
	set("vegetable", 39);
	set("nostrum", 20);
	set("level", 30);
	set("pour_type", "1");
	set("long", "这是一粒白虎夺命丹，雪白透亮。\n");
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

	if (me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi"))
	{
		message_vision("$N没必要吃白虎夺命丹。\n", me);
	}
	else
	{
		me->set("eff_jing", me->query("max_jing"));
		me->set("jing", me->query("eff_jing"));
		me->set("eff_qi", me->query("max_qi"));
		me->set("qi", me->query("eff_qi"));
		message_vision("$N吃下一粒白虎夺命丹，只觉得周身通泰。\n", me);
		destruct(this_object());
	}
	return 1;
}
