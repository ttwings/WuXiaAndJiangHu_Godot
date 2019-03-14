# // Room: /d/baihuagu/treew.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;

extends Room
# var __DIR__ = "/d/baihuagu/"

func create():
	set("short", "树林");
	set("long", """@LONG
丛林中一片黑暗，你瞪大眼睛，只发现到处都是树。你迷路了！
LONG""");
	set("exits", { 
		"east" : __DIR__ + "tree",
	});
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -400);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);

func _init():
	create()
