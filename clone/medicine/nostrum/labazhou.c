// labazou.c 腊八粥

#include <ansi.h>
inherit ITEM;

void setup()
{
}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(GRN "腊八粥" NOR, ({"laba zhou", "zhou", "laba"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "碗");
		set("long", "这是一碗热粥，其中蒸气上冒，兀自有一个个气泡从粥底冲将上来，一碗粥尽作深绿之色，看上去说不出的诡异。闻着药气刺鼻，其毒可知。\n");
		set("value", 50000);
	}
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int force_limit, neili_limit;
	object me = this_player();

	force_limit = me->query_skill("force") * 10;
	neili_limit = me->query("max_neili");

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ((int)me->query_condition("labazhou_drug") > 0)
	{
		me->add("max_neili", -100);
		message_vision(HIR "$N又喝下一碗" GRN "腊八粥" HIR "，只觉得肝肠寸断，五脏欲裂，原来喝得太急太多，药效适得其反！\n" NOR, me);
	}

	else if (neili_limit <= force_limit)
	{
		me->add("max_neili", 50);
		me->add("neili", 50);
		message_vision(HIY "$N喝下一碗" GRN "腊八粥" HIY "，顿然间只觉一股浩荡无比的真气直冲顶门...\n" NOR, this_player());
		me->apply_condition("labazhou_drug", 500);
	}
	me->start_busy(50);
	destruct(this_object());
	return 1;
}
