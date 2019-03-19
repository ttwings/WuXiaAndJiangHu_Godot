# //  Room:  /d/changan/road2.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "大官道");
	set("long", 
"""这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向函谷关，
往西则直达长安城。北边有一条小路通往山里。"""
);
	set("exits",  {
		"north"  :  "/d/village/hsroad1",
		"east"   :  __DIR__ + "hanguguan",
		"west"   :  __DIR__ + "zhongnan",
	});
	set("objects",  {
		"/d/mingjiao/yuan/zhou5" : 1,
		"/d/mingjiao/yuan/wu6" : 1,
		"/d/mingjiao/yuan/zheng7" : 1,
		"/d/mingjiao/yuan/wang8" : 1,
	});
	set("outdoors", "guanzhong");
	set("no_clean_up", 0);
	set("coor/x", -960);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
