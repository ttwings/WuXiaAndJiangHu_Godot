# //  Room:  /d/changan/zhongnan.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "终南山口");
	set_attr("long", 
"""终南山又称太乙山，距长安城八十多里，素有“锦秀巨屏拱长安”
之说。据传老子曾在山中讲经。这条大官道穿越终南山口，两面秀峰入
云，这里却没有一条路可以上山。西面是往长安的大道，东面前往中原。"""
);
	set_attr("exits",  {
		"east"  :  __DIR__ + "road2",
		"west"  :  __DIR__ + "road3",
	});
	set_attr("outdoors", "guanzhong");

	set_attr("no_clean_up", 0);
	set_attr("coor/x", -2000);
	set_attr("coor/y", -10);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);




