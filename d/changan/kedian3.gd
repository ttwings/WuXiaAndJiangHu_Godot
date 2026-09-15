# // /d/changan/kedian3.c

# inherit ROOM;
extends Room

func create():
	set_attr("short", "客店二楼");
	set_attr("long",
"""这是一间很大的客房，陈设十分简陋。靠墙放了十几张小木床，不
少客人正和衣而卧，满屋子都是呼呼的打酣声。西边有张床是空的，你
蹑手蹑脚地走了过去。"""
);
#	set_light(0);
	set_attr("sleep_room", "1");
	set_attr("no_fight", "1");
	set_attr("hotel",1);
	set_attr("no_clean_up", 0);
	set_attr("exits", {
		"out" : __DIR__ + "kedian2",
	});
	set_attr("coor/x", -5050);
	set_attr("coor/y", 1010);
	set_attr("coor/z", 10);
	setup();

# int valid_leave(object me, string dir)
# {
# 	if ( dir == "out" ) me->delete_temp("rent_paid");

# 	return ::valid_leave(me, dir);
# }
