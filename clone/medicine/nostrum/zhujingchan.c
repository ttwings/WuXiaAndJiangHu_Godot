// zhujingchan.c 朱睛冰蟾

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}
void create()
{
	set_name(HIR"朱"NOR"睛"HIC"冰"NOR"蟾"NOR, ({"chan"}));
	set("unit", "只");
	set("value", 40000);
	set("long","这是一千年难得一见的朱睛冰蟾，通体透明，惟眼呈赤色，能解百毒。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me=this_player();

	if (!id(arg))  return notify_fail("你要吃什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	message_vision(HIG"$N吃下一只朱睛冰蟾，只觉一股清香沁入心肺，顿时灵台一片空明，神意清爽！\n" NOR, me);
       if(!userp(me))
	{
	if (me->query_condition("chanchu_poison"))
		me->apply_condition("chanchu_poison",0);
	if (me->query_condition("drunk"))
		me->apply_condition("drunk",0);
	if (me->query_condition("flower_poison"))
		me->apply_condition("flower_poison",0);
	if (me->query_condition("ice_poison"))
		me->apply_condition("ice_poison",0);
	if (me->query_condition("iceshock"))
		me->apply_condition("iceshock",0);
	if (me->query_condition("rose_poison"))
		me->apply_condition("rose_poison",0);
//	if (me->query_condition("sanxiao_poison"))
//		me->apply_condition("sanxiao_poison",0);
	if (me->query_condition("scorpion_poison"))
		me->apply_condition("scorpion_poison",0);
	if (me->query_condition("slumber_drug"))
		me->apply_condition("slumber_drug",0);
	if (me->query_condition("snake_poison"))
		me->apply_condition("snake_poison",0);
	if (me->query_condition("ss_poison"))
		me->apply_condition("ss_poison",0);
	if (me->query_condition("wugong_poison"))
		me->apply_condition("wugong_poison",0);
	if (me->query_condition("xx_poison"))
		me->apply_condition("xx_poison",0);
	if (me->query_condition("xiezi_poison"))
		me->apply_condition("xiezi_poison",0);
	if (me->query_condition("zhizhu_poison"))
		me->apply_condition("zhizhu_poison",0);
	if (me->query_condition("zhua_poison"))
		me->apply_condition("zhua_poison",0);
	if (me->query_condition("ice_sting"))
		me->apply_condition("ice_sting", 0);
	}
	me->start_busy(2);
	destruct(this_object());
	return 1;
}
