// Room: /d/baihuagu/ent.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
void create()
{
	set("short", "小路");
	set("long", @LONG
这是一条羊肠小路，北边是浓郁的大森林，不知道你进去之后
还能不能出来。你走着走着，不禁害怕起来。
LONG);
	set("outdoors", "baihuagu");
	set("exits", ([ 
		"north" : __DIR__"tree",
		"southeast" : "/d/jianzhong/shanlu2",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -400);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
