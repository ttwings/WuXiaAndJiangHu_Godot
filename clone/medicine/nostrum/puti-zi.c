// puti-zi.c 菩提子

#include <ansi.h>

inherit ITEM;

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
	set_name("菩提子", ({"puti zi", "zi"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "颗");
		set("long", "这是一颗晶莹如玉的菩提子，采自灵山佛祖座前，珍稀无比，\n乃万年菩提树之实，功能化百劫，渡千灾，与天地同寿。\n");
		set("value", 500000);
	}
	set("pour_type", "1");
	setup();
}

int do_eat(string arg)
{
	int force_limit, neili_limit, force_skill, add_skill, improve;

	object me = this_player();

	force_limit = me->query_skill("force") * 10;
	neili_limit = me->query("max_neili");
	force_skill = me->query_skill("force", 1);

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要吃什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢吃，小心别噎着了。\n");

	if ((int)me->query_condition("putizi_drug") > 0)
	{
		me->add("max_neili", -100);
		message_vision(HIR "$N又吃下一颗菩提子，只觉得肝肠寸断，五脏欲裂，原来服食太急太多，药效适得其反！\n" NOR, me);
	}
	else if (neili_limit <= force_limit)
	{
		/*		improve = force_limit - neili_limit;

		if ( improve < 100 ) { 
			add_skill = force_skill + (100 - improve)/5 + 1;
			me->set_skill("force", add_skill );
		}
*/
		me->add("max_neili", 100);
		me->add("neili", 100);

		message_vision(HIY "$N吃下一颗菩提子，顿然间只觉一股浩荡无比的真气直冲顶门...\n" NOR, this_player());
		me->apply_condition("putizi_drug", 1000);
	}
	me->unconcious();
	destruct(this_object());
	return 1;
}
