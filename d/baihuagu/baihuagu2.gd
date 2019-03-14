# // Room: /d/baihuagu/baihuagu2.c
# // Last Modified by Winder on Mar. 5 2001
# inherit ROOM;
extends GameObject

# var __DIR__ = "/d/baihuagu/"
# var FILE = null
#include <ansi.h>
func create():
	set("short", HIM + "百花谷内2" + NOR);
	set("long", 
HIG + "只见姹紫嫣红，满山锦绣，彩蝶纷飞，群蜂轻舞。纵是宇外琼地，世外桃源，也不过如此。山坡下一列挂着七八个木制的蜂巢另一面山山坡上盖着三间茅屋。\n"  + NOR);
	set("outdoors", "baihuagu");
	set("exits", {
		"north"    : __DIR__ + "baihuagu",
		"westup"   : __DIR__ + "shanpo1",
		"eastdown" : __DIR__ + "shanpo2",
		"south"    : __DIR__ + "baihuagu1",
		"west"     : __DIR__ + "baihuagu",
		# "east"     : FILE,
	});
	set("objects", []);
	set("no_clean_up", 0);
	set("coor/x", -400);
	set("coor/y", -360);
	set("coor/z", 0);
	setup();

	# replace_program(ROOM);

func _init():
	create()