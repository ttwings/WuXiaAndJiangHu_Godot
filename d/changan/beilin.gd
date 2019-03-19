// /d/changan/beilin.c

// inherit  ROOM;
extends Room
func create():
	set  ("short",  "碑林");
	set  ("long",  """
这里便是天下闻名的长安碑林。相传建于北宋元佑年间。碑林里碑
石墓志林立，自汉至清，荟萃各代名家手笔。真草隶篆，琳琅满目。更
有昭陵六骏浮雕石刻，直看得你眼花缭乱。
""");
	set("exits",  {
		"north"     :  __DIR__ + "westroad1",
		"east"      :  __DIR__ + "zaoxiang",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5060);
	set("coor/y", 990);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
