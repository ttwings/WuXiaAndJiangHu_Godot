// lingzhi.c 灵芝

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(MAG"灵芝"NOR, ({"lingzhi"}));
	set_weight(500);
	set("vegetable", 8);
	set("value", 10000);
	set("nostrum", 1);
	set("unit", "朵");
	set("long", "这是一朵才摘不久的灵芝，看来可以入药。\n");
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

	write("你三口两口就把灵芝吃了下去。渐渐觉得身上有了力气。\n");
	me->set("qi",me->query("eff_qi"));
	destruct(this_object());
	return 1;
}
