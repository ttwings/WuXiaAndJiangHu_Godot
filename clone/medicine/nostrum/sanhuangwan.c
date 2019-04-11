// sanhuangwan.c 三黄宝蜡丸

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY"三黄宝蜡丸"NOR, ({"sanhuang baolawan", "wan"}));
	set("unit", "粒");
	set("vegetable", 104);
	set("nostrum", 51);
	set("level", 140);
	set("value", 10000);
	set("long", "这是一粒三黄宝蜡丸，由麻黄、藤黄、雄黄三味主药配制成。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	object me=this_player();

	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if(!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ( me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi") )
	{
		message_vision("$N没必要吃三黄宝蜡丸。\n",me);
	}
	else
	{
		me->receive_curing("jing", 50);
		me->receive_curing("qi", 100);
		message_vision("$N吃下一粒三黄宝蜡丸，感到丹田一股热气蓬勃而起，直冲全身各处经脉。\n",me);
		destruct(this_object());
	}
	return 1;
}
