// cao.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}
void create()
{
	set_name(HIG "腐心草" NOR, ({"fuxin cao", "cao"}));
	set("unit", "根");
	set("long", "这是一朵无根小草，长得很小，却给人一种欣欣向荣的感觉。\n");
	set("pour_type", "1");
	setup();
}
int do_eat(string arg)
{
	int force_limit, neili_limit;
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	message_vision(HIG "生吃腐心草还不如熬了粥再喝吧。\n" NOR, me);
	force_limit = me->query_skill("force", 1) * 10;
	neili_limit = me->query("max_neili");
	if (neili_limit <= force_limit)
	{
		me->add("max_neili", 5);
		me->start_busy(20);
	}
	message_vision(HIG "$N吃下一株腐心草，顿然间有点肚子疼...\n" NOR, me);
	destruct(this_object());
	return 1;
}
