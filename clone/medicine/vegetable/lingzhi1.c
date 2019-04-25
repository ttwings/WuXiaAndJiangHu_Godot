// lingzhi1.c 灵脂

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "灵脂" NOR, ({"lingzhi"}));
	set_weight(500);
	set("vegetable", 8);
	set("value", 1200);
	set("nostrum", 2);
	set("unit", "块");
	set("long", "这是一块海豹的灵脂，看来可以入药。\n");
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

	write("灵脂不能生吃。\n");
	return 1;
}
