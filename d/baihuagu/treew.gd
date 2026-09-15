# // Room: /d/baihuagu/treew.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;

extends Room
# var __DIR__ = "/d/baihuagu/"

func create():
	set_attr("short", "树林");
	set_attr("long", """@LONG
丛林中一片黑暗，你瞪大眼睛，只发现到处都是树。你迷路了！
LONG""");
	set_attr("exits", { 
		"east" : __DIR__ + "tree",
	});
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -450);
	set_attr("coor/y", -400);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);

func _init():
	create()
