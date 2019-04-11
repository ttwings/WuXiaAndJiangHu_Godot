// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
	remove_call_out("destguo");
	call_out("destguo", 10);
}
void destguo()
{
	message_vision("$N慢慢渗出水来，一会就腐烂掉了。\n",this_object());
	destruct(this_object());
}

void create()
{
	set_name(HIR"人参果"NOR, ({"guo", "renshen guo"}));
	set("unit", "只");
	set("long", "这是一只人参果，已经成型，真的象极了三周不满的小孩。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int force_limit, neili_limit;
	object me = this_player();

	force_limit = me->query_skill("force")*10;
	neili_limit = me->query("max_neili");

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ( neili_limit <= force_limit ) me->add("max_neili", 10);
	me->set("neili", me->query("max_neili"));
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("eff_qi"));
	message_vision("$N吃下一枚人参果，只觉得精神健旺，气血充盈，体内真力源源滋生，甚至不再感到饥饿干渴！\n",me);
	destruct(this_object());
	return 1;
}
