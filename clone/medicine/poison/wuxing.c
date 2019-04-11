// wuxing.c
// inherit F_CLEAN_UP;
inherit COMBINED_ITEM;
#include <ansi.h>

void create()
{

	set_name("无形之毒", ({ "wuxing du","yao"}) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
			"这是一包五毒教的秘制的毒药，吃了它必死无疑。\n你可以用(xpour)命令试试。\n" );
		set("unit", "些");
		set("base_value", 200);
		set("base_unit", "包");
		set("base_weight", 30);
		set("pour_type", "wuxing_poison");
		set("value", 800);
	}
	set_amount(1);
}

void init()
{
	add_action("do_xpour", "xpour");
}

int do_xpour(string arg)
{
	string what;
	object ob,me,who,victim;
//	object *inv;
	function f;
	me = this_player();
	if( !arg || sscanf(arg, "%s in %s", who, what)!=2 || victim == me)
		return notify_fail("命令格式: xpour <人物> in <物品>。\n");
	victim = present(who, environment(me));
	if( !victim || victim==me) return notify_fail("没有你想下毒的人哦。\n");
	if ((string)me->query("family/family_name") != "五毒教")
		return notify_fail("下毒！！你怎么能干这么卑鄙的事哦？\n");
	if ((int)me->query_skill("five_poison", 1) < 50)
		return notify_fail("才这么点本事就想害人？别弱了我五毒教的威名啊！\n");
	ob = present(what, victim);
	if( !ob )
		return notify_fail("对方身上没有" + what + "这样东西。\n");
//	if( me->query_temp("being_toudu") )
//		return notify_fail("你已经在找机会下手了！\n");
	if( ob->query("max_liquid"))
	{
		int myskill = (me->query_skill("poison", 1))*10+me->query("neili");
		int skill = victim->query("neili");
		if((int)ob->query("liquid/remaining")<1)
			return notify_fail("那个容器是空的，不能用来溶解毒粉！\n");
		if (random(myskill)<random(skill))
		{
			tell_object(me, HIR "糟糕！你失手了！\n\n" NOR);
			message_vision("$N一回头，正好发现$n正想向$P身上的" + ob->name() + "下毒！\n\n" + "$N喝道：「干什么！」\n\n", victim, me);
			if( userp(victim) )
			{
				victim->fight_ob(me);
				me->fight_ob(victim);
			}
			else
			{
				victim->kill_ob(me);
				me->kill_ob(victim);
			}
			me->start_busy(3);
			return 1;
		}
		f = (: call_other, __FILE__, "drink_drug" :);
		ob->set("liquid/drink_func", bind(f, ob));
		ob->add("liquid/slumber_effect", 50);
		message("vision","你与" + victim->name() + "擦身而过，偷偷将《" + name() + "》洒进他的" + ob->name()+ "里面。\n", this_player());
		add_amount(-1);
		me->start_busy(2);
		if( random(myskill) < skill/2 )
			message("vision", "你看到" + me->name() + "鬼鬼祟祟地在" + victim->name() + "身上的一" + ob->query("unit") + ob->name() + "里洒入了一些"+name() +"！\n", environment(me), ({ me, victim }) );
		return 1;
	}
	else return notify_fail("毒只能下在饮水里面！\n");
	return 1;
}

int drink_drug(object ob)
{
	this_player()->apply_condition("wuxing_poison", (int)ob->query("liquid/slumber_effect") );
	return 0;
}
