# // /d/changan/dongyuemiao.c

# inherit  ROOM;
extends Room

func  create():
	set("short",  "东岳庙");
	set("long",  
"""东岳就是泰山，历代天子认为山高有灵，因此建庙祭祀。此庙建于
北宋政和六年。大殿宏伟壮观，东西殿墙上画着不少楼阁仕女，远非普
通宗教题材之壁画可比，颇有元明气韵。""");
	set("exits",  {
		"northwest" :  __DIR__ + "zaoxiang",
	});
	set("no_clean_up",  0);
	setup();
	# replace_program(ROOM);

