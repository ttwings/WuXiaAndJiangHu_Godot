// huanzhidan.c 还质丹

inherit ITEM;
#include <ansi.h>

void setup()
{
}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY "三清换质丹" NOR, ({"huanzhi dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "颗");
		set("long", "一颗深黄色的丹药。\n");
		set("value", 10000);
		set("no_sell", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_get", 1);
	}
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么药？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	me->add("neili", 100);
	me->add("jingli", 50);
	if (me->query("jingli") > me->query("max_jingli"))
		me->set("jingli", me->query("max_jingli"));
	message_vision("$N吃下一颗三清换质丹，全身无比的舒坦。\n", me);
	me->start_busy(2);
	destruct(this_object());
	return 1;
}
