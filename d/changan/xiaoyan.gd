# // /d/changan/xiaoyan.c

# inherit  ROOM;
extends Room

func create():
	set("short",  "小雁塔");
	set("long", 
"""小雁塔建于景龙年间，因比大雁塔小，故称小雁塔。塔高十五级，
双塔连理为一塔，形体秀丽美观。"""
);
	set("exits",  {
		"northeast"  :  __DIR__ + "road5",
	});
	set("outdoors",  "changan");
	set("coor/x", -5050);
	set("coor/y", 950);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
