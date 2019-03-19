# // //  Room:  /d/changan/road7.c

# // inherit  ROOM;
extends Room

func create  ():
	set("short",  "官道");
	set("long",
"""一条青石铺就的官道，向西北通往兰州，往东则到达长安。道路两
旁是一片茂密的树林。西边是一座废墟，看起来已经有些年代了。"""
);
	set("exits",  {
		"west"      :  __DIR__ + "apanggong",
		"northwest" :  __DIR__ + "road8",
		"east"      :  __DIR__ + "westgate",
	});
	set("outdoors", "changan");
	set("no_clean_up", 0);
	set("coor/x", -5080);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
