# //  Room:  /d/changan/road9.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "官道");
	set_attr("long", 
"""一条青石铺就的官道，向北通往兰州，往东南则到达长安。道路两
旁是一片茂密的树林。"""
);
	set_attr("exits",  {
		"north"     :  "/d/lanzhou/caoyuan1",
		"southeast" :  __DIR__ + "road8",
	});
	set_attr("outdoors", "changan");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5100);
	set_attr("coor/y", 1020);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
