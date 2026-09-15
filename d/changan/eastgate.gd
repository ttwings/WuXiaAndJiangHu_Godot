
# // /d/changan/eastgate.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "长乐门");
	set_attr("long",  
"""这里便是长安东门----长乐门。长安为多朝古都，果然不同凡响，
城墙以石灰、糯米和土夯成，固若金汤。出了城门是条护城河，几名官
兵正在守门。"""
);
	# //set_attr("item_desc",  {"  ***  "  :  "  ***  ",  });
	set_attr("exits",  {
		"west"  :  __DIR__ + "eastroad1",
		"east"  :  __DIR__ + "baqiao",
	});
	set_attr("objects",  {
		__DIR__ + "npc/wujiang"  :  1,
		__DIR__ + "npc/bing"  :  3,
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5010);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
