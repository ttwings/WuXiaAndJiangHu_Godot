// // /d/changan/northroad1.c

// inherit  ROOM;
extends Room

func create  ():
	set("short",  "北大街");
	set("long",  
"""你正走在长安北大街上。东边是个酒楼，往北就是城门了。西面一
群喇嘛进进出出，原来是个喇嘛庙。里面不知道供的是什么佛爷。"""
);
	set("exits",  {
		"west"  :  __DIR__ + "lamamiao",
		"east"  :  __DIR__ + "jiulou",
		"north" :  __DIR__ + "northgate",
		"south" :  __DIR__ + "northroad2",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5040);
	set("coor/y", 1020);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
