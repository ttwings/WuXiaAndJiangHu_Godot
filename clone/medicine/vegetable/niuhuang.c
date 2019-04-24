// niuhuang.c 牛黄

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY "牛黄" NOR, ({"niuhuang"}));
	set_weight(500);
	set("vegetable", 8);
	set("value", 1000);
	set("nostrum", 16);
	set("unit", "块");
	set("long", "这是一块牛胆里取出来的牛黄，看来可以入药。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	if (!id(arg))
		return notify_fail("你要吃什么？\n");

	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");

	if (arg == "niuhuang")
	{
		write("牛黄不能这么吃。\n");
	}
	return 1;
}
