# //  Room:  /d/changan/road6.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "大官道");
	set_attr("long",  
"""这是一条青石铺就的宽阔笔直的官道，道旁种满了路树，足可容得
下十马并驰。"""
);
	set_attr("exits",  {
		"south"     :  __DIR__ + "northgate",
	});
	set_attr("outdoors", "guanzhong");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 1040);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
