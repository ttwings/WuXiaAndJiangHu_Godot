// heishidan.c 黑石玉洞丹

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}
void create()
{
	set_name(HIB "黑石玉洞丹" NOR, ({"heishi yudongdan", "dan"}));
	set("unit", "粒");
	set("vegetable", 51);
	set("nostrum", 80);
	set("level", 100);
	set("value", 100000);
	set("long", "这是一粒能解百毒的黑石玉洞丹。\n");
	set("pour_type", "1");
	set("no_sell", 1);
	set("no_drop", 1);
	set("no_give", 1);
	set("no_get", 1);
	setup();
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

	message_vision(HIG "$N吃下一粒黑石玉洞丹，只觉一股苦涩的滋味直透心臆。\n" NOR, me);
	if (me->query_condition("chanchu_poison"))
		me->apply_condition("chanchu_poison", 0);
	if (me->query_condition("scorpion_poison"))
		me->apply_condition("scorpion_poison", 0);
	if (me->query_condition("slumber_drug"))
		me->apply_condition("slumber_drug", 0);
	if (me->query_condition("snake_poison"))
		me->apply_condition("snake_poison", 0);
	if (me->query_condition("xiezi_poison"))
		me->apply_condition("xiezi_poison", 0);
	if (me->query_condition("zhizhu_poison"))
		me->apply_condition("zhizhu_poison", 0);
	if (me->query_condition("zhua_poison"))
		me->apply_condition("zhua_poison", 0);
	destruct(this_object());
	me->start_busy(2);
	return 1;
}
