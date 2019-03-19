# // /d/changan/eastroad1.c

# inherit  ROOM;
extends Room

func create  ():
	set("short",  "东大街");
	set("long",  
"""你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以听
到守城官兵的吆喝声，与西边朗朗的读书声混杂在一起。南边是个小铺
子，专门卖一些纪念品。北边是块空地，种着一些花卉。""");
	set("exits",  {
		"west"  :  __DIR__ + "eastroad2",
		"east"  :  __DIR__ + "eastgate",
		"north" :  __DIR__ + "huachang",
		"south" :  __DIR__ + "xiaopu",
	});
	set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5020);
	set("coor/y", 1000);
	set("coor/z", 0);
	setup();
# 	replace_program(ROOM);
# }
