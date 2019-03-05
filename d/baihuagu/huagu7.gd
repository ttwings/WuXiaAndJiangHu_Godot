# // Room: /d/baihuagu/huagu7.c
# // Last Modified by Winder on Mar. 5 2001
# inherit ROOM;

#include <ansi.h>
extends GameObject
var DIR = filename.get_base_dir()
func create():
	set("short", RED + "百花谷" + NOR);
	set("long", 
HIC + "又转了几个弯，迎面两面山壁夹峙三株大松树冲天而起，挡在山壁间。成为两道天然的屏障。\n" + NOR);
	set("exits", 
		{"west" : DIR + "huagu6",}
	);
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -360);
	set("coor/z", 0);
	setup();

func _init():
	create()	

# func init():
# 	add_action("do_swear","swear");
# 	add_action("do_swear","han");
# 	add_action("do_swear","huhan");

# int do_swear(string arg)
# {
# 	if( !arg) return 0;
# 	if( arg == "老顽童" ) 
# 	{
# 		message_vision(HIG "$N朗声喊道：老顽童，小朋友来找你玩儿啦！！！\n"NOR, this_player());
# 		message_vision(HIY "只听见里面呵呵的笑声传来：又有人来找我玩儿了，快进快进！\n"NOR, this_player() );
# 		call_out("close_passage", 10);
# 		set("exits/enter", __DIR__"baihuagu");
# 		return 1;
# 	}
# 	else
# 	{
# 		message_vision(HIG"$N朗声高喊：“"+arg+"！！！”空谷回音，长久不绝。\n"NOR, this_player());
# 		return 1;
# 	}
# }

# void close_passage()
# {
# 	object room;
# 	if( !query("exits/enter") ) return;
# 	delete("exits/enter");
# }
