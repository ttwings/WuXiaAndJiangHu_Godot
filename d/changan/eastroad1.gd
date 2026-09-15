# // /d/changan/eastroad1.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "东大街");
	set_attr("long",  
"""你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以听
到守城官兵的吆喝声，与西边朗朗的读书声混杂在一起。南边是个小铺
子，专门卖一些纪念品。北边是块空地，种着一些花卉。""");
	set_attr("exits",  {
		"west"  :  __DIR__ + "eastroad2",
		"east"  :  __DIR__ + "eastgate",
		"north" :  __DIR__ + "huachang",
		"south" :  __DIR__ + "xiaopu",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5020);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
# 	replace_program(ROOM);
# }
