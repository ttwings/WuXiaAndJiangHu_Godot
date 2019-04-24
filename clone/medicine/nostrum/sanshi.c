// sanshi.c
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIR "三尸脑神丹" NOR, ({"sanshinao shendan", "sanshi dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", 
"一粒火红色的丹药，看样子不是寻常物品。你只可以乘别人人事不知时
喂(wei)给人家吃。\n");
		set("unit", "粒");
		set("value", 20000);
	}
	set("pour_type", "1");
	setup();
}

int init()
{
	add_action("do_wei", "wei");
}

int do_wei(string arg)
{
	object me = this_player(), ob = this_object(), who;

	if (!present(ob, me))
		return 0;
	if (me->query("id") != ob->query("owner"))
		return notify_fail("这不是你练的丹，你喂也没用。\n");
	if (!arg)
		return notify_fail("你要给谁喂三尸脑神丹？\n");
	if (!objectp(who = present(arg, environment(me))))
		return notify_fail("这里没有这个人。\n");
	if (living(who) && !who->query_temp("noliving"))
		return notify_fail("人家有知有觉的，谁肯吃你的臭药？\n");
	message_vision("$N撬开$n的嘴，将" + ob->query("name") + "塞进$n嘴里。\n", me, who);
	who->set("sanshi", me->query("id"));
	destruct(this_object());
	return 1;
}
