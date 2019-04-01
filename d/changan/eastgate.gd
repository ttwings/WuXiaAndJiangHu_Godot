
# // /d/changan/eastgate.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "长乐门");
	set("long",  
"""这里便是长安东门----长乐门。长安为多朝古都，果然不同凡响，
城墙以石灰、糯米和土夯成，固若金汤。出了城门是条护城河，几名官
兵正在守门。"""
);
	# //set("item_desc",  {"  ***  "  :  "  ***  ",  });
	set("exits",  {
		"west"  :  __DIR__ + "eastroad1",
		"east"  :  __DIR__ + "baqiao",
	});
	set("objects",  {
		__DIR__ + "npc/wujiang"  :  1,
		__DIR__ + "npc/bing"  :  3,
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5010);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
