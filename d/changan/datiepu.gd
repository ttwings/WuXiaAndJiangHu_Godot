# // /d/changan/datiepu.c

# inherit  ROOM;
extends Room

func  create  ():
	set("short",  "打铁铺");
	set("long", 
"""这是一家简陋的打铁铺，中心摆着一个火炉，炉火把四周照得一片
通红，你一走进去就感到浑身火热。墙角堆满了已完工和未完工的菜刀、
铁锤、铁棍、匕首、盔甲等物。一位铁匠满头大汗挥舞着铁锤，专心致
志地在打铁。"""
);
	set("exits",  {
		"west"  :  __DIR__ + "southroad2",
	});
	set("objects",  {
		__DIR__ + "npc/tiejiang" : 1,
	});
	set("coor/x", -5030);
	set("coor/y", 990);
	set("coor/z", 0);
	setup();
	# replace_program(ROOM);
