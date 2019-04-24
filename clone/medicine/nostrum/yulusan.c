// yulusan.c 玉露清新散

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
	set_name(HIG "玉露清新散" NOR, ({"yulu qingxinsan", "yulu", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "包");
		set("vegetable", 11);
		set("nostrum", 22);
		set("level", 130);
		set("long", "这是一包淡绿晶莹的玉露清新散。据说乃慕容世家的珍药，提高功力，灵效无比。\n");
		set("value", 10000);
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
	if (me->query_skill_mapped("force") != "shenyuan-gong")
	{
		me->add("max_neili", -10);
		message_vision(HIR "$N吃下一包玉露清新散，只觉得肝肠寸断，原来所练内功不符，反而大损真元！\n" NOR, me);
		//		me->unconcious();
		me->start_busy(10);
	}
	else
	{
		if ((int)me->query_condition("bonze_drug") > 0)
		{
			me->add("max_neili", -1);
			message_vision(HIR "$N吃下一包玉露清新散，只觉得头重脚轻，摇摇欲倒，原来服食太急太多，药效适得其反！\n" NOR, me);
		}
		else if (neili_limit <= force_limit)
		{
			me->add("max_neili", 1);
			message_vision(HIG "$N吃下一包玉露清新散，只觉得体内真力源源滋生，过紫宫，入泥丸\n透十二重楼，遍布奇筋八脉，全身功力顿然提高 !\n" NOR, me);
		}
		me->apply_condition("bonze_drug", 60);
	}
	destruct(this_object());
	return 1;
}
