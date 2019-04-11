// chantui.c 蝉蜕

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name(YEL"蝉蜕"NOR, ({"chantui"}));
	set_weight(500);
	set("vegetable", 1);
	set("value", 2000);
	set("nostrum", 32);
	set("unit", "片");
	set("long", "这是一片风干的蝉蜕，看来可以入药。\n");
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

	write("蝉蜕必须入药才能吃。\n");
	return 1;
}
