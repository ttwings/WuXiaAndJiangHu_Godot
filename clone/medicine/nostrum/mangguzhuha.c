// mangguzhuha.c

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}
void create()
{
	set_name(NOR"莽牯"HIR"朱"NOR"蛤", ({"ha"}));
	set("unit", "只");
	set("value", 40000);
	set("long","莽牯朱蛤是瘟神爷的坐骑，那也是说说罢了。文殊菩萨骑狮子，普贤菩萨骑白象，太上老君骑青牛，这莽牯朱蛤是万毒之王，神通广大，毒性厉害，故老相传，就说它是瘟菩萨的坐骑。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me=this_player();

	if (!id(arg)) return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy() || random(2)==1 )
		return notify_fail("别急，慢慢吃，小心别毒死了。\n");

	message_vision(HIG"$N吃下一只"+name()+HIG"，顿觉精力渐生，全身委顿渐渐消去。\n" NOR, me);
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
	if (me->query_condition("sanxiao_poison"))
		me->apply_condition("sanxiao_poison",0);
	if (me->query_condition("scorpion_poison"))
		me->apply_condition("scorpion_poison",0);
	if (me->query_condition("slumber_drug"))
		me->apply_condition("slumber_drug",0);
	if (me->query_condition("snake_poison"))
		me->apply_condition("snake_poison",0);
	if (me->query_condition("ss_poison"))
		me->apply_condition("ss_poison",0);
	if (me->query_condition("xx_poison"))
		me->apply_condition("xx_poison",0);
	if (me->query_condition("zhua_poison"))
		me->apply_condition("zhua_poison",0);
	me->start_busy(2);
	destruct(this_object());
	return 1;
}
