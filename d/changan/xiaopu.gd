# // /d/changan/xiaopu.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "小铺子");
	set_attr("long", 
"""这是一家专卖旅游纪念品的小铺子。到了长安不买点纪念品，说不
过去吧......一个大嫂正站在铺前向游客招揽生意。"""
);
	set_attr("exits",  {
		"north"  :  __DIR__ + "eastroad1",
	});
	set_attr("objects",  {
		__DIR__ + "npc/dasao": 1,
	});
	set_attr("coor/x", -5020);
	set_attr("coor/y", 990);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
