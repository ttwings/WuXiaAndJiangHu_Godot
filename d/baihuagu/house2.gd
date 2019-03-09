# // Room: /d/baihuagu/house2.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
#include <ansi.h>
extends Room
var __DIR__ = "/d/baihuagu/"
func create():
	set("short", HIY + "周伯通居" + NOR);
	set("long", "这是间很简陋的屋子，陈设简单，由此可见老顽童极于玩而不极于物。\n");
	set("exits", {
		"west"  : __DIR__ + "house1",
		"north" : __DIR__ + "shanpo1",
	});
	set("objects", {});
	set("no_clean_up", 0);
	set("coor/x", -410);
	set("coor/y", -370);
	set("coor/z", 10);
	# setup();
	# replace_program(ROOM);

func _init():
	create()