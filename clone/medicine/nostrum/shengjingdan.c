// shengjingdan.c 生精丹

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG"凌霄生精丹"NOR, ({"shengjing dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "一颗碧绿色的丹药。此乃全真异宝。\n");
		set("no_sell", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_get", 1);
	}
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int taoism_limit, jingli_limit;
	object me = this_player();

	taoism_limit = me->query_skill("taoism", 1)*10;
	jingli_limit = me->query("max_jingli");
	
	if (!id(arg)) return notify_fail("你要吃什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ( (int)me->query_condition("quanzhen_drug" ) > 0 )
		return notify_fail("你是否才炼丹药或才服食了丹药？你的全身气血未归位，不宜吃丹药。\n");

	if ( me->query_skill_mapped("force") != "xiantian-qigong" )
	{
		me->add("max_jingli", -10);
		message_vision(HIR "$N吃下一颗凌霄生精丹，只觉得腹痛如搅，全身如被抽气般的空虚。原来此丹不适你所练内功，结果大损真元！\n" NOR, me);
		me->start_busy(10);
	}
	else
	{
		me->start_busy(2);
		if ( jingli_limit <= taoism_limit  )
		{
			me->add("max_jingli", 1);
			message_vision(HIG "$N吃下一颗凌霄生精丹，只觉得体内精力源源滋生，全身顿时觉得舒畅无比！\n" NOR, me);
		}
		else
			message_vision(HIG "$N吃下一颗凌霄生精丹，也没觉得有什么感觉。\n" NOR, me);

		me->apply_condition("quanzhen_drug", 50);
	}
	destruct(this_object());
	return 1;
}

