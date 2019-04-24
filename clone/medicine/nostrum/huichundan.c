// huichundan.c 回春丹
// Last Modified by Winder on Mar. 5 2001

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "回春丹" NOR, ({"huichun dan", "dan"}));
	set("unit", "粒");
	set("vegetable", 0);
	set("nostrum", 0);
	set("level", 300);
	set("long", "这是一粒清绿剔透的回春丹。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢喝，小心别呛着了。\n");

	if (me->query("age") <= 39)
	{
		message_vision("$N没必要吃回春丹。\n", me);
	}
	else
	{
		me->add("mud_age", -86400);
		me->add("vegetable/huichun", 1);
		me->delete ("last_slp");
		me->delete ("jingzuo_time");
		message_vision("$N吃下一粒回春丹，伸了个懒腰，觉得身子骨灵便了许多。\n", me);
		destruct(this_object());
	}
	return 1;
}
