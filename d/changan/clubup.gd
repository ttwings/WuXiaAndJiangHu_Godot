extends Room

func  create():
	set_attr("short",  "长安二楼");
	set_attr("long",  
"""乐坊楼上显得格外热闹，走廊里人来人往，几间屋子里人声嘈杂，
牌签骨骰钱币落盘的声音不绝。看样子，客人们赌得正欢呢。"""
); 
        # //set_attr("item_desc",  {"  ***  "  :  "  ***  ",  });
	set_attr("exits",  {
        "up"  :  __DIR__ + "clubpoem",
		"west"  :  __DIR__ + "duchang1",
        "east"  :  __DIR__ + "duchang2",
        "north"  :  __DIR__ + "duchang3",
        "south"  :  __DIR__ + "duchang4",
        "down"  :  __DIR__ + "club",
        });
	set_attr("objects",  {
# //               __DIR__"npc/libai"  :  1,
                 __DIR__  + "obj/tables"  :  3,
        });
# //      set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5030);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 10);
	setup();
	# replace_program(ROOM);
