#// // /d/changan/northroad1.c
#
#// inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "北大街");
	set_attr("long",  
"""你正走在长安北大街上。东边是个酒楼，往北就是城门了。西面一
群喇嘛进进出出，原来是个喇嘛庙。里面不知道供的是什么佛爷。"""
);
	set_attr("exits",  {
		"west"  :  __DIR__ + "lamamiao",
		"east"  :  __DIR__ + "jiulou",
		"north" :  __DIR__ + "northgate",
		"south" :  __DIR__ + "northroad2",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 1020);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
