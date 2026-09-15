# // /d/changan/westroad2.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "西大街");
	set_attr("long",  
"""你正走在长安西大街上，毕竟曾为多朝古都，气派非比寻常。北边
是鼓楼，相传当年天子曾在此鸣鼓点将，往南可以到长安城内有名的“
清馨”茶馆。"""
);
	set_attr("exits",  {
		"west"  :  __DIR__ + "westroad1",
		"east"  :  __DIR__ + "center",
		"north" :  __DIR__ + "gulou",
		"south" :  __DIR__ + "zaoxiang",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5050);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
