# // /d/changan/northroad2.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "北大街");
	set_attr("long", 
"""你正走在长安北大街上。西边是一家钱庄，可以听到叮叮当当的金
银声音。东边个兵营，长安守军驻扎在内，不时传来操练之声。"""
);
	set_attr("exits",  {
		"west"  :  __DIR__ + "qianzhuang",
		"east"  :  __DIR__ + "bingying",
		"north" :  __DIR__ + "northroad1",
		"south" :  __DIR__ + "center",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
