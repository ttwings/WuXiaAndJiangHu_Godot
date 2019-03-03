// Room: /d/baihuagu/bhgent.c
// Last Modified by Winder on Mar. 5 2001
inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", HIW"茫茫雪地");
	set("long",
HIW"这里是白茫茫的一片雪地，" NOR"远处山峰层峦迭嶂。前面隐隐约约
好象有一个山谷。阵阵花香飘过来，好象还夹杂着鸟的欢唱。\n"
	);
	set("outdoors", "baihuagu");
	set("exits", ([ 
		"south" : __DIR__"out",
		"north" : __DIR__"huagu1",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -380);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
