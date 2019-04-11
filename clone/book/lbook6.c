// lbook6.c
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(YEL"「史记」"NOR, ({ "literateb6", "shu6", "book6" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "卷");
		set("value", 1000);
		set("long", "一本很古旧的线装书，兰皮上写着两个篆字'史记'，里面的内容很多都已经模糊不清。\n");
		set("material", "paper");
	}
}
void init()
{
	add_action("do_read","study");
	add_action("do_read","du");
}
int do_read(string arg)
{
	object me;
	me = this_player();
	if (!present(this_object(), this_player())) return 0;

	if( arg=="literateb6" || arg=="shu6" || arg=="book6")
	{
		write("这本书太破旧了，现在没法读。\n");
		return 1;
	}
}
