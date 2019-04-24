// tianwangdan.c 天王保命丹
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name("天王保命丹", ({"baoming dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "颗");
		set("value", 4000);
		set("long", "这天王保命丹是由三百年老山人参、白熊胆、雪莲等物炼成的灵丹。\n");
		set("medicine", 1);
		set("no_drop", "天王保命丹炼制，哪能乱扔！ \n");
	}

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
		message_vision("$N没必要吃天王保命丹。\n", me);
	}
	else
	{
		me->receive_curing("jing", 250);
		me->receive_curing("qi", 400);
		message_vision("$N吃下一粒天王保命丹，顿时觉得好多了。\n", me);
		destruct(this_object());
	}
	return 1;
}
