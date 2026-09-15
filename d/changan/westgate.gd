# // /d/changan/westgate.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "安定门");
	set_attr("long", 
"""这里便是长安西门----安定门。长安为多朝古都，果然不同凡响，
城墙以石灰、糯米和土夯成，固若金汤。出城往西门便可直通兰州，几
名官兵正在守门。"""
);
        # //set_attr("item_desc",  {"  ***  "  :  "  ***  ",  });
	set_attr("exits",  {
            "west"  :  __DIR__ + "road7",
            "east"  :  __DIR__ + "westroad1",
        });

	set_attr("objects",  {
                __DIR__ + "npc/wujiang"  :  1,
                __DIR__ + "npc/bing"  :  1,
        });
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5070);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
        # replace_program(ROOM);

