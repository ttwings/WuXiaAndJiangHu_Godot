// ganmao.c 感冒药

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIW "特效感冒药" NOR, ({"texiao yao", "ganmao yao", "yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "包");
		set("long", "这是一包特效感冒药，用的是平一指的独家配方。\n" +
						"对各种感冒病症都有显著疗效。\n");
		set("value", 20000);
	}
	setup();
}

int do_eat(string arg)
{
	object me = this_player();
	if (!id(arg))
		return 0;
	if (me->is_busy())
		return notify_fail("别急，慢慢来。\n");
	if (!me->query_condition("ill_kesou") &&
		!me->query_condition("ill_shanghan") &&
		!me->query_condition("ill_fashao") &&
		!me->query_condition("ill_dongshang") &&
		!me->query_condition("ill_zhongshu"))
	{
		write("你现在又没有感冒，别乱吃药。\n");
		return 1;
	}
	else
	{
		me->clear_condition("ill_kesou");
		me->clear_condition("ill_shanghan");
		me->clear_condition("ill_fashao");
		me->clear_condition("ill_dongshang");
		me->clear_condition("ill_zhongshu");
		message_vision(HIY "$N服下一包特效感冒药，感冒症状缓解了许多。\n" NOR, me);
		me->start_busy(3);
		destruct(this_object());
		return 1;
	}
}
