# // /d/changan/kedian3.c

# inherit ROOM;
extends Room

func create():
	set("short", "客店二楼");
	set("long",
"""这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，不
少客人正和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，你
蹑手蹑脚地走了过去。"""
);
#	set_light(0);
	set("sleep_room", "1");
	set("no_fight", "1");
	set("hotel",1);
	set("no_clean_up", 0);
	set("exits", {
		"out" : __DIR__ + "kedian2",
	});
	set("coor/x", -5050);
	set("coor/y", 1010);
	set("coor/z", 10);
	setup();

# int valid_leave(object me, string dir)
# {
# 	if ( dir == "out" ) me->delete_temp("rent_paid");

# 	return ::valid_leave(me, dir);
# }
