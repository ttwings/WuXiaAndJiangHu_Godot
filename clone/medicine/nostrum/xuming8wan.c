// xuming8wan.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW "续命八丸" NOR, ({"xuming bawan", "bawan", "8wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "粒");
		set("vegetable", 86);
		set("nostrum", 121);
		set("no_sell", 1);
		set("level", 160);
		set("long", "这是花了一十二年时光，采集千年人参、伏苓、灵芝、鹿茸、首乌、灵脂、熊胆、三七、麝香种种珍贵之极的药物，九蒸九晒，制成八颗起死回生的“续命八丸”。有的极臭，有的极苦，有的入口如刀割，有的辛辣如火炙。只要吞服了这“续命八丸”，不论多大的内伤外伤，定然起死回生。\n");
		set("value", 0);
	}
	set("pour_type", "1");
	setup();
}

int init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
	remove_call_out("destwan");
	call_out("destwan", 60);
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

	if (!wizardp(me) &&
		(!me->query("dietime") || time() - me->query("dietime") > 600))
	{
		write("你现在不宜吃续命八丸了。\n");
		return 1;
	}
	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");
	message_vision("$N吃下一粒" + name() + "。\n", me);
	log_file("eat_dan", sprintf("[%s] %s eat xuming8wan \n", ctime(time()), geteuid(me)));
	me->delete ("dietime");
	me->reincarnate();
	me->add("combat_exp", (int)(me->query("combat_exp") / 49));
	me->add("potential", me->query("potential") - me->query("learned_points"));
	//me->add("max_neili", 2);
	//	me->set("shen", 0);
	//	me->set("score", 0);
	//	me->set("meili", 0);
	//	me->set("weiwang", 0);
	if ((int)me->query("score") < 5000)
		me->set("score", 0);
	else
		me->add("score", -5000);
	me->skillreincarnate();
	me->start_busy(10);
	destruct(this_object());
	return 1;
}

void destwan()
{
	message_vision("$N慢慢干涸化成灰，一会就飘落地上消失了。\n", this_object());
	destruct(this_object());
}
