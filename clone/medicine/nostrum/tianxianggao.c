// tianxianggao.c 天香断续膏

inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_fu", "fu");
}

void create()
{
	set_name(HIY "天香断续膏" NOR, ({"tianxiang duanxugao", "gao"}));
	set("unit", "块");
	set("vegetable", 25);
	set("nostrum", 13);
	set("level", 50);
	set("long", "这是一块天香断续膏，是恒山派的疗伤圣药。受伤之后，适时敷(fu)药，当有起死之功。\n");
	set("pour_type", "1");
	setup();
}

int do_fu(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要敷什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要敷什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢敷，小心别敷歪了。\n");

	if (me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi") &&
		me->query("neili") >= me->query("max_neili"))
	{
		message_vision("$N没必要敷天香断续膏。\n", me);
	}
	else
	{
		me->set("eff_jing", me->query("max_jing"));
		me->set("jing", me->query("eff_jing"));
		me->set("eff_qi", me->query("max_qi"));
		me->set("qi", me->query("eff_qi"));
		me->add("neili", me->query("max_neili"));
		message_vision("$N拿出一块天香断续膏，运内力捂热后，“啪”地一声，敷在创口上。\n", me);
		destruct(this_object());
	}
	return 1;
}
