# // /d/changan/club.c

# inherit  ROOM;
extends Room

func  create  ():
	set("short",  "长安乐坊");
	set("long",  
"""这里是长安城一家有名的娱乐场所。当夜幕降临后，这里就格外热
闹。进进出出的客人有达官贵人，南来北往的商旅，浪迹天涯的游子，
三五成群的兵士，有时也能看见一些作俗客打扮的僧人或道士。"""
);
       # //set("item_desc",  {"  ***  "  :  "  ***  ",  });
	set("exits",  {
		"up"    :  __DIR__ + "clubup",
		"south" :  __DIR__ + "eastroad2",
       });
	set("objects",  {
                __DIR__ + "obj/tables"  :  1,
                __DIR__ + "obj/chairs"  :  2,
       });
# //                set("outdoors",  "changan");
	set("no_clean_up",  0);
	set("coor/x", -5030);
	set("coor/y", 1010);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
