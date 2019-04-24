// baicaodan.c 百草丹

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIG "百草丹" NOR, ({"baicao dan", "dan"}));
	set("unit", "粒");
	set("vegetable", 36);
	set("nostrum", 25);
	set("level", 70);
	set("pour_type", "1");
	set("long", "这是一粒碧绿透亮的百草丹，很是可爱。\n");
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

	if (me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi"))
	{
		message_vision("$N没必要吃百草丹。\n", me);
	}
	else
	{
		me->receive_curing("jing", 50);
		me->receive_curing("qi", 100);
		message_vision("$N吃下一粒百草丹，舌底生津，渐渐有了力气。\n", me);
		destruct(this_object());
	}
	return 1;
}
