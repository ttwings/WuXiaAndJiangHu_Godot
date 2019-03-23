# // /d/changan/southroad2.c

# inherit  ROOM;
extends Room

func create():
	set("short",  "南大街");
	set("long",  
"""你正走在长安南大街上，北边是一个热闹的广场，人声鼎沸，东边
不时地传来金属撞击声，和西边安静的小巷形成鲜明的对比。"""
);
	set("exits",  {
		"north" :  __DIR__ + "center",
		"south" :  __DIR__ + "southroad1",
		"west"  :  __DIR__ + "zaoxiang",
		"east"  :  __DIR__ + "datiepu",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5040);
	set("coor/y", 990);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
