// huochan.c
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
	message_vision("$N全身慢慢变黑，一会就歪头死掉了。\n", this_object());
	destruct(this_object());
}

void create()
{
	set_name(HIR "火蟾" NOR, ({"huo chan", "chan"}));
	set("unit", "只");
	set("long", "这是一只生长在昆仑山顶的火蟾，两眼投射出夺目的红光。\n");
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
		me->add("max_neili", 5);
	me->set("neili", me->query("max_neili"));
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("eff_qi"));
	message_vision(HIY "$N吃下一只火蟾，只觉一股热线自咽而下，沿督脉直冲玄关，一股真力源源不绝汇入丹田。\n" NOR, me);
	destruct(this_object());
	return 1;
}
