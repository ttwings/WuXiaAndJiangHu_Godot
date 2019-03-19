# //  Room:  /d/changan/road4.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "大官道");
	set("long",  
"""这是一条宽阔笔直的官道，足可容得下十马并驰。往东南通向函谷
关，往西则直达长安城。"""
);
	set("exits",  {
		"west"      :  __DIR__ + "baqiao",
		"southeast" :  __DIR__ + "road3",
	});
	set("outdoors", "guanzhong");
	set("no_clean_up", 0);
	set("coor/x", -4000);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
