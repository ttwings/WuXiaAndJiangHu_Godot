# // /d/changan/eastroad2.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "东大街");
	set_attr("long", 
"""你正走在长安东大街上，一条宽阔的青石板街道，向东西两头延伸。
南边是一座简朴的院子，半月形的大门上方写着“关中书院”四个烫金
大字，苍劲有力。里面不时地传来学生们抑扬顿挫的读书声，和北边嘈
杂之声混杂在一起。北面就是长安乐坊了。"""
);
	set_attr("exits",  {
		"west"  :  __DIR__ + "center",
		"east"  :  __DIR__ + "eastroad1",
		"north" :  __DIR__ + "club",
		"south" :  __DIR__ + "shuyuan",
	});
	set_attr("outdoors",  "changan");
	set_attr("no_clean_up",  0);
	set_attr("coor/x", -5030);
	set_attr("coor/y", 1000);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
