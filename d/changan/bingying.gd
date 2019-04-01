# // /d/changan/bingyin.c

# #include <room.h>
# inherit ROOM;
extends Room

func create():
	set("short", "兵营");
	set("long", """
这里是长安守军驻扎地，一对官兵正在操练。你最好赶紧走开，不
然被随便安个罪名关进大牢可不是好玩的。
""" );
	set("exits", {
		"west" : __DIR__ + "northroad2",
	});
	set("objects", {
		__DIR__ + "npc/wujiang" : random(2) + 1,
		__DIR__ + "npc/bing" : random(2) + 1,
	});
	set("outdoors", "changan");
	set("coor/x", -5030);
	set("coor/y", 1010);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
