// guiyuandan.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"归元丹"NOR, ({"guiyuan dan", "dan"}));
	if (clonep())
	{
		set_default_object(__FILE__);
	}
	else {
		set("unit", "粒");
		set("long", "归元丹是峨嵋弟子一身精血所化，珍贵无比，有生死
肉骨之功，为武林至宝。\n");
		set("value", 0);
	}
	set("pour_type", "1");
	seteuid(this_player()->query("id"));
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

	if( !me->query("dietime") || time()-me->query("dietime") > 480)
		return notify_fail("你现在不宜吃归元丹了。\n");
	if(!id(arg)) return notify_fail("你要吃什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要吃什么？\n");
	if( me->query_skill("linji-zhuang", 1) < 180 )
		return notify_fail("你未曾修成幽冥庄，恐怕吃不得此丹。\n");
	if( me->is_busy() )
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");
	message_vision("$N吃下一粒" + name() + "。\n", me);
	log_file("eat_dan", sprintf("[%s] %s eat guiyuan \n", ctime(time()), geteuid(me)));
	me->delete("dietime");
	me->reincarnate();
	me->add("combat_exp", (int)me->query("combat_exp") / 49);
//	me->add("potential", 50);
	me->add("max_neili", 2);
	me->skillreincarnate();
	me->start_busy(2);
	destruct(this_object());
	return 1;
}

