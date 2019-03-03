// Room: /d/baihuagu/baihuagu1.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", HIM"百花谷内"NOR);
	set("long", 
HIG"只见姹紫嫣红，满山锦绣，彩蝶纷飞，群蜂轻舞。纵是宇外琼地，
世外桃源，也不过如此。\n"NOR);
	set("outdoors", "baihuagu");
	set("exits", ([
		"north" : __DIR__"baihuagu",
		"south" : __FILE__,
		"west"  : __DIR__"baihuagu",
		"east"  : __DIR__"baihuagu2",
	]));
	set("objects", ([
	]));
	set("no_clean_up", 0);
	set("coor/x", -430);
	set("coor/y", -360);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
