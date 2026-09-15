# // /d/changan/xiaoyan.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "小雁塔");
	set_attr("long", 
"""小雁塔建于景龙年间，因比大雁塔小，故称小雁塔。塔高十五级，
双塔连理为一塔，形体秀丽美观。"""
);
	set_attr("exits",  {
		"northeast"  :  __DIR__ + "road5",
	});
	set_attr("outdoors",  "changan");
	set_attr("coor/x", -5050);
	set_attr("coor/y", 950);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
