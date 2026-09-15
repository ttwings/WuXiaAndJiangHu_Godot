# // /d/changan/southroad1.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "南大街");
	set_attr("long",
"""你正走在长安南大街上，南大街乃是城里的繁华地段，几个客商正
将货物贩往杂货铺。往南可以看到南门，东边则是个热闹的杂货铺。"""
);
	set_attr("exits",  {
		"north" :  __DIR__ + "southroad2",
		"south" :  __DIR__ + "southgate",
		"west"  :  __DIR__ + "yizhan",
		"east"  :  __DIR__ + "zahuopu",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 980);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
