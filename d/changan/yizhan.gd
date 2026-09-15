# // /d/changan/yizhan.c

# inherit  ROOM;
extends Room

func create():
	set_attr("short",  "驿站");
	set_attr("long", 
"""这里是长安驿站。由于各个城市进出长安的物资传送都要通过这里，
因此驿站里人群进进出出，一片忙碌的景象。站前竖着一溜石桩，绑着
一些驿马和大车，几个车夫正在四处招揽生意。"""
);
	set_attr("exits",  {
		"east"  :  __DIR__ + "southroad1",
	});
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5050);
	set_attr("coor/y", 980);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
