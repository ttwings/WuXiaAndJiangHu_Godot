// yangyandan.c 养颜丹
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
	set_name(HIW "养颜丹" NOR, ({"yangyan dan", "dan"}));
	set("unit", "粒");
	set("vegetable", 0);
	set("nostrum", 0);
	set("level", 300);
	set("long", "这是一粒玉雪可爱的养颜丹。\n");
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

	if (me->query("per") >= 40)
	{
		message_vision("$N没必要吃养颜丹。\n", me);
	}
	else
	{
		me->add("per", 1);
		message_vision("$N吃下一粒养颜丹，下意识地伸手摸了摸脸，觉得似乎皱纹是比原来少了点。\n", me);
		destruct(this_object());
	}
	return 1;
}
