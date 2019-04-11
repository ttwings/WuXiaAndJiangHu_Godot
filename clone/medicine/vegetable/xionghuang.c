// xionghuang.c 雄黄

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(HIY"雄黄"NOR, ({"xionghuang" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "包");
		set("vegetable", 32);
		set("nostrum", 1);
		set("long", "这是一包雄黄，据说可驱百毒。\n");
		set("value", 1000);
	}
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

	return notify_fail("想死啊？雄黄不能吃。\n");
}

