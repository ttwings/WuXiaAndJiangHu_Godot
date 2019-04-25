// laoshanshen.c 老山参

inherit ITEM;
#include <ansi.h>
void setup()
{
}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY "老山参" NOR, ({"laoshan shen", "shen"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "株");
		set("vegetable", 4);
		set("nostrum", 64);
		set("long", "这是一株沾满山泥的长白老山参。\n");
		set("value", 10000);
	}
	set("pour_type", "1");
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

	me->receive_curing("qi", 200);
	message_vision("$N吃下一株老山参，顿觉浑身一股热气兜底冒了上来！\n", me);
	destruct(this_object());
	return 1;
}
