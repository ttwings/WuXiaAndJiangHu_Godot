# // Room: /d/baihuagu/house3.c
# // Last Modified by Winder on Mar. 5 2001

# inherit ROOM;
#include <ansi.h>
extends Room
# var __DIR__ = "/d/baihuagu/"
func create():
	set_attr("short", HIY + "周伯通居" + NOR);
	set_attr("long", 
"这是间很简陋的屋子，陈设简单，由此可见老顽童极于玩而不极于物。\n");
	set_attr("exits",{ 
		"south":  __DIR__ + "house1",
	});
	set_attr("no_fight", 1);
	set_attr("objects", {          
		__DIR__ + "npc/zhou":1});
	set_attr("coor/x", -420);
	set_attr("coor/y", -360);
	set_attr("coor/z", 10);
# 	setup();
# 	replace_program(ROOM);
# }

func _init():
	create()
