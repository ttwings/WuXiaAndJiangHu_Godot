# // /d/changan/kuixinglou.c

# inherit  ROOM;
extends Room

func create  ():
	set_attr("short",  "奎星楼");
	set_attr("long", 
"""这是永宁门上的一个城楼，极目四望，可以看到南边青青的终南山。
旁边几个官兵正在休息。不过这里是军事重地，你最好还是赶快离开。"""
);
	set_attr("exits",  {
		"down"  :  __DIR__ + "southgate",
	});
	set_attr("objects",  {
		"/d/city/npc/wujiang" : random(3),
		"/d/city/npc/bing" : random(3),
	});
	set_attr("outdoors",  "changan");
	set_attr("coor/x", -5040);
	set_attr("coor/y", 970);
	set_attr("coor/z", 10);
	setup();
	# replace_program(ROOM);
