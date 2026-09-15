# // /d/changan/shuyuan.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "关中书院");
	set_attr("long", 
"""关中书院是甘陕地区最高学府，建于明万历年间。一位庄重严肃的
老者坐在太师椅上讲学，那就是当今大儒冯先生了。在他的两侧坐满了
求学的学生。"""
);
	set_attr("exits",  {
		"north"  :  __DIR__ + "eastroad2",
	});
	set_attr("objects",  {
		__DIR__ + "npc/feng" : 1,
		"clone/food/apple" : 1
	});
	set_attr("coor/x", -5030);
	set_attr("coor/y", 990);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
