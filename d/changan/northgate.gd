# // /d/changan/northgate.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "安远门");
	set("long", 
"""这里便是长安北门----安远门。长安为多朝古都，果然不同凡响，
城墙以石灰、糯米和土夯成，固若金汤。一条官道自北门向北延伸，官
兵们警惕地注视着过往行人。"""
;
	# //set("item_desc",  {"  ***  "  :  "  ***  ",  });
	set("exits",  {
		"north"  :  __DIR__ + "road6",
		"south"  :  __DIR__ + "northroad1",
	});
	set("objects",  {
		"/d/city/npc/wujiang"  :  1,
		"/d/city/npc/bing"  :  3,
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5040);
	set("coor/y", 1030);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
