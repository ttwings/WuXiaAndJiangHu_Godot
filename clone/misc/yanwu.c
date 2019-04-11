// Yanwu.c 烟雾弹
#include <command.h>
#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIM"烟雾弹"NOR, ({ "yanwu"}) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一颗特制的烟雾弹。它可以用(apply)来逃命。\n");
		set("unit","些");
		set("base_unit", "颗");
		set("value", 1000);
		set("no_drop", RED"难道你想制造混乱吗？\n"NOR);
	}
	set_amount(1);
}

void init()
{
	add_action("do_apply","apply");
}
int do_apply(string arg)
{
	object me,ob;
	object *inv;
	int i;

	if (!id(arg))
		return 0;

	me=this_player();
	if (!present(this_object(),this_player())) return 0;
	if (me->is_busy())
		return notify_fail("你正在忙着呢。\n");

	inv = all_inventory(environment(me));
	for(i=0; i<sizeof(inv); i++)
	{
		ob=inv[i];
		if (ob==me)
		continue;
		if( (ob->is_character()) && (!ob->is_corpse()) )
		{
			if (!ob->is_busy())
			ob->start_busy(1);
		}
	}
	me->set_temp("no_follow",1);
	tell_room(environment(me),HIM"地面突然腾出一股桃红色的烟雾，大家什么也看
不见，陷入混乱之中。\n"NOR);

	GO_CMD->do_flee(me);
	this_object()->add_amount(-1);
	return 1;
}
void owner_is_killed()
{
	object me = this_player();
	write(HIM"只见一阵桃红色的烟雾闪过...尸体上什么东西消失了。\n"NOR);
	destruct(this_object());
}
int query_autoload()
{
	return 1;
}
