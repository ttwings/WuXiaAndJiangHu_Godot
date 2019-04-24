// baixianwan.c 百涎丸

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIW "百涎丸" NOR, ({"baixian wan", "wan"}));
	set("unit", "粒");
	set("vegetable", 36);
	set("nostrum", 25);
	set("level", 70);
	set("pour_type", "1");
	set("long", "这是一粒百涎丸，看上去白熙熙的，还透着亮光，不知道吃了会...\n");
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

	message_vision(HIG "$N吃下一粒百涎丸，只觉得胸内气血翻腾，啊...！吃错药了！！！\n" NOR, me);
	me->set("qi", 10);
	me->set("jing", 10);
	destruct(this_object());
	return 1;
}
