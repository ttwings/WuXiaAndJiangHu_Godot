# // Room: /d/baihuagu/baihuagu.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
extends Room
#include <ansi.h>
# var DIR = "/d/baihuagu/"
var FILE = null

func create():
	set("short", HIM + "百花谷内" + NOR);
	set("long", 
HIG + "只见姹紫嫣红，满山锦绣，彩蝶纷飞，群蜂轻舞。纵是宇外琼地，世外桃源，也不过如此。\n" + NOR);
	set("outdoors", "baihuagu");
	set("exits",{ 
		"out"   : __DIR__ + "huagu7",
		"south" : __DIR__ + "baihuagu1",
		# "north" : __FILE__,
		# "west"  : FILE,
		# "east"  : FILE,
	})
	set("objects",[]);
	set("no_clean_up", 0);
	set("coor/x", -430);
	set("coor/y", -360);
	set("coor/z", 0);
	print_debug(__DIR__)
	# setup();
	# replace_program(ROOM);
#}

func _init():
	create()
