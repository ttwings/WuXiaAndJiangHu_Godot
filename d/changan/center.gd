# // /d/changan/center.c

# inherit  ROOM;
extends Room
func create():
	set("short",  "中央广场");
	set("long",  """
			这里便是长安城的中心，东南西北四条大街交汇于此。广场中央一
			座巍峨高大的钟楼耸立于前，和市北的鼓楼遥相呼应，很是有些气势。
			每到清晨，响亮的钟声便会伴着淡淡雾气传向长安城的大街小巷。路口
			车水马龙，来往人潮不断。
		""");
	# //set("item_desc",  {"  ***  "  :  "  ***  ",  });

	set("exits",  {
		"north" :  __DIR__ + "northroad2",
		"south" :  __DIR__ + "southroad2",
		"west"  :  __DIR__ + "westroad2",
		"east"  :  __DIR__ + "eastroad2",
		"up"    :  __DIR__ + "zhonglou",
	});
	set("objects",  {
# //		__DIR__"npc/libai"  :  1,
	});
	set("outdoors",  "changan");
	set("coor/x", -5040);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
# }
