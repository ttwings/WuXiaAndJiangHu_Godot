# //  Room:  /d/changan/road4.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "大官道");
	set_attr("long",  
"""这是一条宽阔笔直的官道，足可容得下十马并驰。往东南通向函谷
关，往西则直达长安城。"""
);
	set_attr("exits",  {
		"west"      :  __DIR__ + "baqiao",
		"southeast" :  __DIR__ + "road3",
	});
	set_attr("outdoors", "guanzhong");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -4000);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
