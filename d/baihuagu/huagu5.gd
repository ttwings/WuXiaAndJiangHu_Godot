# // Room: /d/baihuagu/huagu5.c
# // Last Modified by Winder on Mar. 5 2001
# inherit ROOM;

#include <ansi.h>
extends GameObject
# var __DIR__ = "/d/baihuagu/"

func create():
	set_attr("short", HIR + "百花谷5" + NOR);
	set_attr("long", 
HIG + "来到此处，你突然眼前一亮，但觉青青翠谷，点缀着或红或紫，或黄或白的鲜花，竟是换了一个世界。道旁有一株桃树，开得正艳。\n" + NOR);  
	set_attr("outdoors", "baihuagu");
	set_attr("exits", {
		"east" :__DIR__ + "huagu4",
		"north":__DIR__ + "huagu2",
		"south":__DIR__ + "huagu6",
		"west" :__DIR__ + "huagu5",
	});
	set_attr("objects", {});
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -450);
	set_attr("coor/y", -360);
	set_attr("coor/z", 0);
	# setup();
	# replace_program(ROOM);

func _init():
	create()
