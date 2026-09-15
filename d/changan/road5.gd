# //  Room:  /d/changan/road5.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "大官道");
	set_attr("long", 
"""这是一条青石铺就的宽阔笔直的官道，道旁种满了路树，足可容得
下十马并驰。往东南通向大雁塔，往西南通向小雁塔。往北则直达长安
城。"""
);
	set_attr("exits",  {
		"north"     :  __DIR__ + "southgate",
		"southeast" :  __DIR__ + "dayan",
		"southwest" :  __DIR__ + "xiaoyan",
	});
	set_attr("outdoors", "guanzhong");
	set_attr("no_clean_up", 0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 960);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
