# // /d/changan/zaoxiang.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "枣巷");
	set_attr("long",
"""你走在一条幽静的青石小巷中，巷两边种着一行枣树。不料繁华的
长安城内也有如此悠然去处。一阵枣香、一丝茶意、一声丝竹如远处高
楼的歌声，隐隐飘来。"""
)
	set_attr("exits",  {
		"north"     :  __DIR__ + "westroad2",
		"southwest" :  __DIR__ + "chaguan",
		"southeast" :  __DIR__ + "dongyuemiao",
		"west"      :  __DIR__ + "beilin",
		"east"      :  __DIR__ + "southroad2",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5050);
	set_attr("coor/y", 990);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
