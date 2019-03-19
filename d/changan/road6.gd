# //  Room:  /d/changan/road6.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "大官道");
	set("long",  
"""这是一条青石铺就的宽阔笔直的官道，道旁种满了路树，足可容得
下十马并驰。"""
);
	set("exits",  {
		"south"     :  __DIR__ + "northgate",
	});
	set("outdoors", "guanzhong");
	set("no_clean_up", 0);
	set("coor/x", -5040);
	set("coor/y", 1040);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
