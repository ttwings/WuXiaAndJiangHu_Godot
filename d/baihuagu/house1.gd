# // Room: /d/baihuagu/house1.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
# #include <ansi.h>
extends Room
# var __DIR__ = "/d/baihuagu/"
func create():
	set_attr("short", HIY + "周伯通居" + NOR);
	set_attr("long", "这是间很简陋的屋子，陈设简单，由此可见老顽童极于玩而不极于物。屋角边靠着一张床。\n");
	set_attr("sleep_room", "1");
	set_attr("exits", 
		{"east"  : __DIR__ + "house2",
		"north" : __DIR__ + "house3",}
	);
	set_attr("objects", {});
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -420);
	set_attr("coor/y", -370);
	set_attr("coor/z", 10);
	# setup();
	# replace_program(ROOM);

func _init():
	create()
