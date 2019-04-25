// Last Modified by winder on Apr. 25 2001
// zhanshu.c

#include <ansi.h>
inherit ITEM;
int is_zhanshu() { return 1; }

void create()
{
	set_name(HIR "挑战书" NOR, ({"zhan shu", "shu", "book"}));
	set_weight(200);
	seteuid(getuid());
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一张七杀门首领天杀星的挑战书(kan)。\n");
		set("value", 5000);
		set("material", "paper");
	}
}

void init()
{
	add_action("do_kan", "kan");
}

int do_kan(string arg)
{
	if (!id(arg))
		return notify_fail("你想看什么？\n");
	write(HIR "            《生死之约》\n\n" NOR);
	write(WHT "    限你在十分钟之内北京天安门广场与我决\n");
	write(WHT "一死战，不来者就是狗熊！\n\n");
	write(WHT "                      七杀门首领：" HIR "天杀星\n" NOR);
	return 1;
}
