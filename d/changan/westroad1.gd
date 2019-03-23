# // /d/changan/westroad1.c

# inherit  ROOM;
extends Room

func create():
	set("short",  "西大街");
	set("long", 
"""你正走在长安西大街上，毕竟曾为多朝古都，气派非比寻常。南边
是碑林，北边是个热闹的客栈，来自各地的人们进进出出，据说也是情
人们的幽会地点。"""
);
	set("exits",  {
		"west"  :  __DIR__ + "westgate",
		"east"  :  __DIR__ + "westroad2",
		"north" :  __DIR__ + "kedian",
		"south" :  __DIR__ + "beilin",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5060);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
