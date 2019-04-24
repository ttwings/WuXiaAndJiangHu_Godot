// jinyinhua.c 金银花

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(YEL "金" HIW "银" HIY "花" NOR, ({"jinyinhua"}));
	set_weight(500);
	set("vegetable", 4);
	set("value", 30);
	set("nostrum", 16);
	set("unit", "根");
	set("long", "这是一根的金银花，看来可以入药。\n");
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

	write("金银花入药才能入口。\n");
	return 1;
}
