# // /d/changan/jiulou.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "谪仙楼");
	set("long", 
"""这里就是天下闻名的谪仙楼，就是李太白醉中做神仙的地方。可是
你刚走进去，就看见一块牌子：暂不营业。世人皆知，天下美酒，北有
汾酒，南有绍酒。最好的汾酒不在山西，而就在这里。你闻着满楼酒香，
原来都是从地窖中飘出来的。"""
);
	set("exits",  {
		"down"  :  __DIR__ + "dijiao",
		"west"  :  __DIR__ + "northroad1",
	});
	set("no_clean_up", 0);
	set("coor/x", -5030);
	set("coor/y", 1020);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);