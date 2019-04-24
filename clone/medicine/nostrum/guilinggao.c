// gao.c 龟苓膏

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "龟苓膏" NOR, ({"guiling gao", "gao"}));
	set_weight(3000);
	set("unit", "块");
	set("long", "这是一块用乌龟甲和茯苓配置成的龟苓膏，功能延年益寿。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int taoism_limit, jingli_limit;
	object me = this_player();

	taoism_limit = me->query_skill("taoism", 1) * 10;
	jingli_limit = me->query("max_jingli");

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	me->start_busy(2);
	if (jingli_limit <= taoism_limit && jingli_limit < 500)
	{
		write(YEL "你吃下了一块龟苓膏，只觉得精神健旺之极，精力直欲奔腾而出。\n" NOR);
		me->add("max_jingli", 20);
		me->add("jingli", 20);
	}
	else
		write("你吃下了一块龟苓膏，但是好象没什么用。\n");

	destruct(this_object());
	return 1;
}
