# // /d/changan/westroad2.c

# inherit  ROOM;
extends Room

func create  ():
	set  ("short",  "西大街");
	set  ("long",  
"""你正走在长安西大街上，毕竟曾为多朝古都，气派非比寻常。北边
是鼓楼，相传当年天子曾在此鸣鼓点将，往南可以到长安城内有名的“
清馨”茶馆。"""
);
	set("exits",  {
		"west"  :  __DIR__ + "westroad1",
		"east"  :  __DIR__ + "center",
		"north" :  __DIR__ + "gulou",
		"south" :  __DIR__ + "zaoxiang",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5050);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
