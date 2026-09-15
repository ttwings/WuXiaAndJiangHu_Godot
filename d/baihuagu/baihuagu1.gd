# // Room: /d/baihuagu/baihuagu1.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
extends Room
# var FILE = null
#include <ansi.h>
func create():
	set_attr("short", HIM + "百花谷内1" + NOR);
	set_attr("long", HIG + "只见姹紫嫣红，满山锦绣，彩蝶纷飞，群蜂轻舞。纵是宇外琼地，世外桃源，也不过如此。\n" + NOR);
	set_attr("outdoors", "baihuagu");
	set_attr("exits", {
		"north" : __DIR__ + "baihuagu",
		# "south" : FILE,
		"west"  : __DIR__ + "baihuagu",
		"east"  : __DIR__ + "baihuagu2",
	});
	set_attr("objects", [
	]);
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -430);
	set_attr("coor/y", -360);
	set_attr("coor/z", 0);
	# setup();
	# replace_program(ROOM);

func _init():
	create()
