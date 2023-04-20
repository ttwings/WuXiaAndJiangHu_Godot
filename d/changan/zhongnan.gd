# //  Room:  /d/changan/zhongnan.c

# inherit  ROOM;
extends Room

func create():
	set("short",  "终南山口");
	set("long", 
"""终南山又称太乙山，距长安城八十多里，素有“锦秀巨屏拱长安”
之说。据传老子曾在山中讲经。这条大官道穿越终南山口，两面秀峰入
云，这里却没有一条路可以上山。西面是往长安的大道，东面前往中原。"""
);
	set("exits",  {
		"east"  :  __DIR__ + "road2",
		"west"  :  __DIR__ + "road3",
	});
	set("outdoors", "guanzhong");

	set("no_clean_up", 0);
	set("coor/x", -2000);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);




