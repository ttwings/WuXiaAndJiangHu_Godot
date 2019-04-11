// medicine: xuelian.c
// Last Modified by winder on Sep. 27 2001

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name("天山雪莲", ({"xuelian", "lian", "lotus"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "株");
		set("vegetable", 32);
		set("nostrum", 4);
		set("long", "这是一株只有在寒冷的地方才能生长的雪莲。\n");
		set("value", 100);
	}
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ((int)me->query("eff_qi") == (int)me->query("max_qi"))
		return notify_fail("你现在不用吃这宝贝！\n");
	me->receive_curing("qi",200);
	message_vision("$N小心地吃下一株雪莲，顿时觉得神清气爽了不少！\n", me);
	destruct(this_object());
	return 1;
}

