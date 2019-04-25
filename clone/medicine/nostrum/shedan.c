// shedan.c 蟒蛇胆
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
	remove_call_out("decay");
	call_out("decay", 180);
}

void create()
{
	set_name(HIG "蟒蛇胆" NOR, ({"dan", "she dan"}));
	set("unit", "副");
	set("long", "这是一副蟒蛇胆，碧绿如蓝。\n");
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int taoism_limit, jingli_limit;
	object me = this_player();

	taoism_limit = me->query_skill("taoism", 1) * 10;
	jingli_limit = me->query("max_jingli");

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if (jingli_limit <= taoism_limit)
		me->add("max_jingli", 1);
	me->set("qi", me->query("eff_qi"));
	message_vision("$N吃下一副蟒蛇胆，只觉得耳聪目明，精力陡长。\n", me);
	destruct(this_object());
	return 1;
}

void decay()
{
	object where = environment(this_object());
	if (interactive(where))
		message("vision", BLU "蟒蛇胆啪的一声破了，弄得你一身甚是腥臭。\n" NOR,
				where);
	else
		message("vision", BLU "蟒蛇胆啪的一声破了，蛇血流了一地。\n" NOR,
				where);
	destruct(this_object());
}
