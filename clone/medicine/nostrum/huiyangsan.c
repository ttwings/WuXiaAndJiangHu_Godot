// huiyangsan.c 回阳九龙散

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(RED"回阳九龙散"NOR, ({"huiyangjiulong san", "san"}));
	set("unit", "包");
	set("vegetable", 14);
	set("nostrum", 46);
	set("level", 90);
	set("long", "这是一包回阳九龙散，是崆峒派的疗伤圣药。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me=this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ( me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi") &&
		me->query("neili") >= me->query("max_neili"))
	{
		message_vision("$N没必要吃回阳九龙散。\n",me);
	}
	else
	{
		me->receive_recuring("jing", 200);
		me->receive_recuring("qi", 300);
//		me->set("neili", me->query("max_neili"));
		me->add("neili",150);
		message_vision("$N吃下一包回阳九龙散，感到全身一阵暖洋洋的，十分舒服。\n",me);
		destruct(this_object());
	}
	return 1;
}
