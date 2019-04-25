// badou.c 巴豆

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "巴豆" NOR, ({"badou"}));
	set_weight(500);
	set("unit", "粒");
	set("vegetable", 1);
	set("value", 1000);
	set("nostrum", 1);
	set("long", "这是一粒绿油油的巴豆，看来可以入药。\n");
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

	write("你一口就把巴豆吃了下去。结果蹲下就拉，拉得头晕眼花。\n");
	me->set("qi", 1);
	destruct(this_object());
	return 1;
}
