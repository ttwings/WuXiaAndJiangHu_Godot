# // /d/changan/dayan.c

# // inherit  ROOM;
extends Room

func  create():
	set_attr("short",  "大雁塔");
	set_attr("long",  
"""唐永徽三年，圣僧玄奘为保护佛家经书，由唐高宗资助建成此塔。
在《三藏法师传》卷三中记载：摩揭国有一寺，一雁离群落羽，摔死地
上，僧以为雁即菩萨，建塔纪念，故名大雁塔。
""");
	set_attr("exits",  {
		"northwest"  :  __DIR__ + "road5",
	});
	set_attr("outdoors",  "changan");
	set_attr("coor/x", -5030);
	set_attr("coor/y", 950);
	set_attr("coor/z", 0);
	setup();
	# replace_program(ROOM);
