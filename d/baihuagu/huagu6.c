// Room: /d/baihuagu/huagu6.c
// Last Modified by Winder on Mar. 5 2001
inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", HIR"百花谷"NOR);
	set("long", 
HIG"来到此处，你突然眼前一亮，但觉青青翠谷，点缀着或红或紫，
或黄或白的鲜花，竟是换了一个世界。道旁有一株桃树，开得正艳。\n"NOR);  
	set("outdoors", "baihuagu");
	set("exits", ([
		"north":__DIR__"huagu5",
		"east" :__DIR__"huagu7",
		"west" :__DIR__"huagu3",
		"south":__DIR__"huagu6",
	]));
	set("objects", ([
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -360);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
