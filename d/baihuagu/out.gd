# // Room: /d/baihuagu/out.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
extends Room
# var __DIR__ = "/d/baihuagu/"
func create():
	set("short", "树林外");
	set("long", """@LONG
眼前一片光明，比起树林里的黑暗，简直有点刺眼。南边是一
片阴森森的大树林，相信你是不敢再进去了。
LONG""");
	set("outdoors", "baihuagu");
	set("exits", { 
		"south" : __DIR__ + "tree",
		"north" : __DIR__ + "bhgent",
	});
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -400);
	set("coor/z", 0);
	# setup();
	# replace_program(ROOM);

func _init():
	create()
