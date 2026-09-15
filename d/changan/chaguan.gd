# // /d/changan/chaguan.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "清馨茶馆");
	set_attr("long",  """
你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙
桌一字排开，坐满了客人。一位老者正在堂前弹奏，几个儒生击几而歌。
的确是个悠然去处。
""");
	set_attr("exits",  {
		"northeast" :  __DIR__ + "zaoxiang",
	});
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5060);
	set_attr("coor/y", 980);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
