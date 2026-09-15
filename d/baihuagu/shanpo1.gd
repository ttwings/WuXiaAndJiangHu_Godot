# // // Room: /d/baihuagu/shanpo1.c
# // // Last Modified by Winder on Mar. 5 2001

# // inherit ROOM;
# // #include <ansi.h>
extends Room
# var __DIR__ = "/d/baihuagu/"
# todo
var VEGETABLE_DIR = "res://"
func create():
	set_attr("short", HIY + "山坡" + NOR);
	set_attr("long", 
"这是一面山坡，山势甚为平坦。山坡上有几间茅屋。\n");
	set_attr("outdoors", "baihuagu");
	set_attr("count", 3);
	set_attr("exits", {
		"south"    : __DIR__ + "house2",
		"eastdown" : __DIR__ + "baihuagu2",
	});
	set_attr("objects", {           
	});
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -410);
	set_attr("coor/y", -360);
	set_attr("coor/z", 10);
	setup();

func _init():
	create()
	add_action("do_dig","dig");

func do_dig():
	var me;
	var food;
	me=this_player();
	if query("count") > 0:
		message_vision("你挖了一会儿，挖到一颗茯苓。\n",me);
		food=new_ob(VEGETABLE_DIR + "fuling");
		food.move(me);
		add("count", -1);
	else: message_vision("你挖了一会儿，没挖到什么。\n",me);
