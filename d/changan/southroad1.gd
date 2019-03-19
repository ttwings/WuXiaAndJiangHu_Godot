# // /d/changan/southroad1.c

# inherit  ROOM;
extends Room

func create  ():
	set  ("short",  "南大街");
	set  ("long",
"""你正走在长安南大街上，南大街乃是城里的繁华地段，几个客商正
将货物贩往杂货铺。往南可以看到南门，东边则是个热闹的杂货铺。"""
);
	set("exits",  {
		"north" :  __DIR__ + "southroad2",
		"south" :  __DIR__ + "southgate",
		"west"  :  __DIR__ + "yizhan",
		"east"  :  __DIR__ + "zahuopu",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5040);
	set("coor/y", 980);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
