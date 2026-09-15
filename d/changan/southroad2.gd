# // /d/changan/southroad2.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "南大街");
	set_attr("long",  
"""你正走在长安南大街上，北边是一个热闹的广场，人声鼎沸，东边
不时地传来金属撞击声，和西边安静的小巷形成鲜明的对比。"""
);
	set_attr("exits",  {
		"north" :  __DIR__ + "center",
		"south" :  __DIR__ + "southroad1",
		"west"  :  __DIR__ + "zaoxiang",
		"east"  :  __DIR__ + "datiepu",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 990);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
