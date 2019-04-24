// jieqiwan.c
inherit ITEM;
#include <ansi.h>

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
	set_name(MAG "九转结气丸" NOR, ({"jieqi wan", "jieqi", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "颗");
		set("vegetable", 15);
		set("nostrum", 82);
		set("level", 110);
		set("long", "这是一颗透着紫红色调的九转结气丸。此丸乃武当珍药，提高功力，灵效无比。\n");
		set("value", 100);
		set("no_drop", "这样东西不能离开你。\n");
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

	me->start_busy(2);
	if (me->query_skill_mapped("force") != "taiji-shengong")
	{
		me->add("max_neili", -10);
		message_vision(HIR "$N吃下一颗九转结气丸，只觉得肝肠寸断，原来所练内功不符，反而大损真元！\n" NOR, me);
		//		me->unconcious();
		me->start_busy(10);
	}
	else
	{
		if ((int)me->query_condition("taoist_drug") > 0)
		{
			me->add("max_neili", -1);
			message_vision(HIR "$N吃下一颗九转结气丸，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
		}
		else if (neili_limit <= force_limit)
		{
			me->add("max_neili", 1);
			message_vision(HIG "$N吃下一颗九转结气丸，只觉浑身真气游走，过紫宫，入泥丸\n透十二重楼，遍布奇筋八脉！\n" NOR, me);
		}
		me->apply_condition("taoist_drug", 60);
	}
	destruct(this_object());
	return 1;
}
