# // /d/changan/kedian.c

# inherit ROOM;
extends Room

func create():
	set("short", "云来客栈");
	set("long",
"""这是一家兴隆的客栈，门口挂着块匾，上书“客似云来”。据说是
米芾的墨宝。店小二里里一边招呼客人，一边大声介绍米芾和客栈的渊
源，神色甚为得意。墙上挂着一个牌子(paizi),想来不是什么墨宝，写
的歪歪扭扭。"""
 );
	set("no_fight", 1);
	set("valid_startroom", 1);
	set("no_sleep_room",1);
# //	set("no_clean_up", 0);
	set("item_desc", {
		"paizi" : "楼上雅房，每夜五十两白银。\n",
	});
	set("objects", {
		"/d/city/npc/xiaoer" : 1,
	});
	set("exits", {
		"north" : __DIR__ + "majiu",
		"south" : __DIR__ + "westroad1",
		"up"    : __DIR__ + "kedian2",
	});

	set("coor/x", -5060);
	set("coor/y", 1010);
	set("coor/z", 0);
	setup();
	# "/clone/board/kedian10_b"->foo();
# }

# int valid_leave(object me, string dir)
# {

# 	if ( !me->query_temp("rent_paid") && dir == "up" )
# 	return notify_fail("店小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊！\n");

# 	if ( me->query_temp("rent_paid") && dir == "south" )
# 	return notify_fail("店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！
# 旁人还以为小店伺候不周呢！\n");

# 	return ::valid_leave(me, dir);
# }
