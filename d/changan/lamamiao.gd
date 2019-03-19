# // /d/changan/lamamiao.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "喇嘛庙");
	set("long", 
"""这里原是西北和康藏一带喇嘛进京时的住宿地，后来建成格鲁派（
黄教）寺庙。由于这里进出都是喇嘛，因此大家都叫这里喇嘛庙。真名
广仁寺反而没多少人知道。寺门高挂康熙御书“慈云西荫”匾额一块。"""
);
	set("exits",  {
		"east"  :  __DIR__ + "northroad1",
	});
	set("outdoors",  "changan");
	set("coor/x", -5050);
	set("coor/y", 1020);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
