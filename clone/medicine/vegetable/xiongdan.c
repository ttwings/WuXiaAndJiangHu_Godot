// xiongdan.c 熊胆

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(GRN "熊胆" NOR, ({"xiong dan", "dan"}));
	set_weight(1000);
	set("vegetable", 16);
	set("value", 2400);
	set("nostrum", 64);
	set("unit", "颗");
	set("long", "这是一颗暗绿色的熊胆，看来可以入药。\n");
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

	me->set("eff_qi", me->query("max_qi"));
	message_vision("$N吃下一副熊胆，觉得精神好多了。\n", me);
	destruct(this_object());
	return 1;
}
