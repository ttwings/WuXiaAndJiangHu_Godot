# //  Room:  /d/changan/road3.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "大官道");
	set_attr("long", 
"""这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向函谷关，
往西北则直达长安城。"""
);
	set_attr("exits",  {
		"northwest" :  __DIR__ + "road4",
		"east"      :  __DIR__ + "zhongnan",
		"west"      :  "/d/hanzhong/guandao1",
	});
	set_attr("outdoors", "guanzhong");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -3000);
	set_attr("coor/y", -10);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
