# //  Room:  /d/changan/road1.c

# inherit  ROOM;

extends Room

func create  ():
	set("short",  "关洛道");
	set("long",  
"""这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向六朝古
都，天心之麓的洛阳城。"""
);
	set("exits",  {
		"east"  :  "/d/luoyang/westgate",
		"west"  :  __DIR__ + "hanguguan",
	});
	set("objects",  {
		"/d/mingjiao/yuan/zhaomin" : 1,
		"/d/mingjiao/yuan/zhao1" : 1,
		"/d/mingjiao/yuan/qian2" : 1,
		"/d/mingjiao/yuan/sun3" : 1,
		"/d/mingjiao/yuan/li4" : 1,
	});
	set("outdoors", "guanzhong");
	set("coor/x", -800);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
