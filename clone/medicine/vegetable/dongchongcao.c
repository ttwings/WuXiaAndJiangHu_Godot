// dongchongcao.c 冬虫草

#include <ansi.h>
inherit ITEM;

void setup()
{
}

void init()
{
	add_action("do_fu", "fu");
}

void create()
{
	set_name(HIB "冬虫草" NOR, ({"dongchong cao", "cao"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "株");
		set("long", HIB "这是一株夏季从冬季钻入土中的死虫身上长出的冬虫夏草。受伤了敷上有奇效。\n" NOR);
		set("value", 2500);
	}
	set("pour_type", "1");
	setup();
}

int do_fu(string arg)
{
	string what = query("cure");
	int howmuch = query("amount");
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要敷什么？\n");
	if (!present(this_object(), me))
		return notify_fail("你要敷什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢敷，小心别敷歪了。\n");

	if ((int)me->query("eff_qi") == (int)me->query("max_qi"))
		return notify_fail("你现在身上没有受到任何伤害！\n");
	else
	{
		me->receive_curing("qi", 150);
		message_vision("$N把一株冬虫草放进口中嚼碎，小心敷在伤口上，气色看起来好多了。\n", me);
		destruct(this_object());
		return 1;
	}
}
