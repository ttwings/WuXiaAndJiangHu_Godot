# // /d/changan/southgate.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "永宁门");
	set_attr("long",
"""这里便是长安南门----永宁门。长安为多朝古都，果然不同凡响，
城墙以石灰、糯米和土夯成，固若金汤。出了城门便是官道，几名官兵
正在守门。还有几名不当值的官兵正在门楼上休息。"""
);
#	//set_attr("item_desc",  {"  ***  "  :  "  ***  ",  });
	set_attr("exits",  {
		"north"  :  __DIR__ + "southroad1",
		"south"  :  __DIR__ + "road5",
		"up"     :  __DIR__ + "kuixinglou",
	});
	set_attr("objects",  {
		"/d/city/npc/wujiang"  :  1,
		"/d/city/npc/bing"  :  3,
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5040);
	set_attr("coor/y", 970);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
