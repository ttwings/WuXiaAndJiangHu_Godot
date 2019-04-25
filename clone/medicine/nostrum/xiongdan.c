// xiongdan.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
	remove_call_out("destdan");
	call_out("destdan", 10);
}

void destdan()
{
	object ob;
	message_vision("$N慢慢被风吹着，一会就不再新鲜了。\n", this_object());
	ob = new ("/clone/medicine/vegetable/xiongdan");
	ob->move(environment(this_object()));
	destruct(this_object());
}

void create()
{
	set_name(HIG "新鲜熊胆" NOR, ({"dan", "xiong dan"}));
	set("unit", "副");
	set("long", "这是一副碧绿色的新鲜熊胆，热气腾腾的，十分诱人。\n");
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

	if (neili_limit <= force_limit)
		me->add("max_neili", 2);
	me->set("neili", me->query("max_neili"));
	me->set("qi", me->query("eff_qi"));
	message_vision("$N吃下一副新鲜熊胆，只觉得精神健旺，体内真力源源滋生，气血充盈。\n", me);

	destruct(this_object());
	return 1;
}
