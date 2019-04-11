// chuanshanjia.c 穿山甲

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(GRN"穿山甲"NOR, ({"chuanshanjia"}));
	set_weight(500);
	set("vegetable", 2);
	set("value", 1000);
	set("nostrum", 1);
	set("unit", "只");
	set("long", "这是一只烤制过的穿山甲，看来可以入药。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me = this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	write("穿山甲吃不得。\n");
	return 1;
}
