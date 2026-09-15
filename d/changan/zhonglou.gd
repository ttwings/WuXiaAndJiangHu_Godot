# // /d/changan/zhonglou.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "钟楼");
	set_attr("long", 
"""钟楼建于明洪武一十三年。青条石为方基，巨木为塔楼。楼内悬挂
巨钟一口，用以报时，钟楼因此得名。楼前是个热闹的广场，西南可以
看到天下闻名的碑林，西北和钟楼遥相呼应。"""
);
	set_attr("exits",  {
		"down"  :  __DIR__ + "center",
	});
	set_attr("outdoors",  "changan");
	set_attr("coor/x", -5040);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 10);
	setup();
	# replace_program(ROOM);
