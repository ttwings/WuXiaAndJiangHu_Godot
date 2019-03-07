# // Room: /d/baihuagu/huagu1.c
# // Last Modified by Winder on Mar. 5 2001
# inherit ROOM;

# #include <ansi.h>
extends Room
var __DIR__ = "res://d/baihuagu/"
func create():
	set("short", MAG + "百花谷" + NOR);
	set("long", 
HIR + "来到此处，你突然眼前一亮，但觉青青翠谷，点缀着或红或紫，或黄或白的鲜花，竟是换了一个世界。道旁有一株桃树，开得正艳。\n" + NOR);  
	set("outdoors", "baihuagu");
	set("exits", {
		"enter": __DIR__ + "huagu2",
		"south": __DIR__ + "bhgent",
	});
	set("objects", {});
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -370);
	set("coor/z", 0);
	setup();

func init():
	create()
	# if(interactive(this_player()))
	# {
	# 	remove_call_out("dropleaf");
	# 	call_out("dropleaf",random(10)+10,this_player());

func dropleaf(me:GameObject):
	var leaf:GameObject;
	# if(me)
	# if(environment(me) == this_object())
	# 	tell_object(me,HIM"一枝桃花随风飘下．．．．\n"NOR);
	# 	leaf = new(__DIR__"obj/leaf");
	# 	leaf->move(this_object());      
