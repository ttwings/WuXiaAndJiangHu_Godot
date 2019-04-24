// sanxiaosan.c
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("三笑逍遥散", ({"sanxiaoxiaoyao san", "xiaoyao san", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一包无色的粉末, 看样子不是寻常物品. \n");
		set("unit", "包");
		set("pour_type", "sanxiao_poison");
		set("value", 20000);
	}
	setup();
}

int init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
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

	if (arg == "san" || arg == "xiaoyao san")
	{
		message_vision("$N仰头咽下一包" + name() + "。\n", me);
		me->set_temp("die_reason", "吃下" + name() + ",自杀身亡了");
		this_player()->die();
		destruct(this_object());
	}
	return 1;
}
