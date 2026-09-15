# // /d/changan/huachang.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "花场");
	set_attr("long",  
"""虽说洛阳牡丹闻名天下，但长安菊花却也毫不逊色。这片空地满种
“黄金甲”，黄巢在世，想必是十分喜欢的了。"""
);
	set_attr("exits",  {
		"south"  :  __DIR__ + "eastroad1",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5020);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
