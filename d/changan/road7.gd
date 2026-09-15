# // //  Room:  /d/changan/road7.c

# // inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "官道");
	set_attr("long",
"""一条青石铺就的官道，向西北通往兰州，往东则到达长安。道路两
旁是一片茂密的树林。西边是一座废墟，看起来已经有些年代了。"""
);
	set_attr("exits",  {
		"west"      :  __DIR__ + "apanggong",
		"northwest" :  __DIR__ + "road8",
		"east"      :  __DIR__ + "westgate",
	});
	set_attr("outdoors", "changan");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5080);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
