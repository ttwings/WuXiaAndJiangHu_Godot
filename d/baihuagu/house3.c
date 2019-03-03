// Room: /d/baihuagu/house3.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", HIY"周伯通居"NOR);
	set("long", 
"这是间很简陋的屋子，陈设简单，由此可见老顽童极于玩而
不极于物。\n");
	set("exits", ([
		"south":  __DIR__"house1",
	]));
	set("no_fight", 1);
	set("objects", ([           
		__DIR__"npc/zhou":1]));
	set("coor/x", -420);
	set("coor/y", -360);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

