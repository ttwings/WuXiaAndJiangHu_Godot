# // /d/changan/zhonglou.c

# inherit  ROOM;
extends Room

func create  ():
	set  ("short",  "钟楼");
	set  ("long", 
"""钟楼建于明洪武一十三年。青条石为方基，巨木为塔楼。楼内悬挂
巨钟一口，用以报时，钟楼因此得名。楼前是个热闹的广场，西南可以
看到天下闻名的碑林，西北和钟楼遥相呼应。"""
);
	set("exits",  {
		"down"  :  __DIR__ + "center",
	});
	set("outdoors",  "changan");
	set("coor/x", -5040);
	set("coor/y", 1000);
	set("coor/z", 10);
	setup();
	# replace_program(ROOM);
