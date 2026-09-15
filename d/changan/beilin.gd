#// /d/changan/beilin.c
#
#// inherit  ROOM;
extends Room
func create():
	set_attr("short",  "碑林");
	set_attr("long",  """
这里便是天下闻名的长安碑林。相传建于北宋元佑年间。碑林里碑
石墓志林立，自汉至清，荟萃各代名家手笔。真草隶篆，琳琅满目。更
有昭陵六骏浮雕石刻，直看得你眼花缭乱。
""");
	set_attr("exits",  {
		"north"     :  __DIR__ + "westroad1",
		"east"      :  __DIR__ + "zaoxiang",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5060);
	set_attr("coor/y", 990);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
