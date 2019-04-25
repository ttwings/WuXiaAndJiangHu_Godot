// /clone/board/jail_b.c
#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
	set_name(HIG "我的自供状" NOR, ({"board"}));
	set("location", "/d/beijing/jail");
	set("board_id", "jail_b");
	set("long", HIB "我不是人，我是畜生。我对不起养育我的父母啊! \n" NOR);
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
