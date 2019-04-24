// shedangao.c
inherit ITEM;
void init()
{
	add_action("do_eat", "eat");
	add_action("do_eat", "fu");
}

void create()
{
	set_name("蛇胆膏", ({"shedan gao", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "块");
		set("long", "这是珍贵补品『蛇胆膏』。\n");
		set("value", 100);
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

	if ((me->query("max_jing") >= 110) || (me->query("max_qi") >= 200))
		return notify_fail("你吃『蛇胆膏』已无效用！\n");
	if (me->query("max_jing") < 105)
	{
		me->add("max_jing", 2);
		me->add("eff_jing", 2);
		me->add("jing", 4);
		me->add("max_qi", 5);
		me->add("eff_qi", 5);
		me->add("qi", 10);
	}
	else
	{
		me->add("max_jing", 1);
		me->add("eff_jing", 1);
		me->add("jing", 2);
		me->add("max_qi", 3);
		me->add("eff_qi", 3);
		me->add("qi", 5);
	}
	message_vision("$N吃下一块蛇胆膏，顿觉一股浩荡真气直涌上来，精，气大增...\n", me);
	destruct(this_object());
	return 1;
}
