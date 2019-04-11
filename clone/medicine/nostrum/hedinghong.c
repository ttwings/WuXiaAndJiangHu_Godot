// Pill: hedinghong.c
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(RED"鹤顶红"NOR, ({"heding hong", "hong"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一瓶剧毒的毒药, 如果用来炼暗器有见血封喉之效. \n");
		set("unit", "瓶");
		set("value", 20000);
	}
	set("pour_type", "1");
	setup();
}

int init()
{
	add_action("do_drink", "drink");
	add_action("do_drink", "he");
}

int do_drink(string arg)
{
	object me = this_player();

	if(!id(arg)) return notify_fail("你要喝什么？\n");
	if(!present(this_object(), this_player()))
		return notify_fail("你要喝什么？\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢喝，小心别呛着了。\n");

	message_vision("$N仰头咕嘟咕嘟灌下一瓶" + name() + "。\n", me);
	me->set_temp("die_reason","喝下鹤顶红，自杀身亡了");
	me->die();
	destruct(this_object());
	return 1;
}
