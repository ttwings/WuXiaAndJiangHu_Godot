
# //  Room:  /d/changan/road8.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "官道");
	set_attr("long", 
"""一条青石铺就的官道，向西北通往兰州，往东南则到达长安。道路
两旁是一片茂密的树林。"""
);
	set_attr("exits",  {
		"northwest" :  __DIR__ + "road9",
		"southeast" :  __DIR__ + "road7",
	});
	set_attr("outdoors", "changan");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5090);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
