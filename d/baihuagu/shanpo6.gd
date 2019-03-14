# // Room: /d/baihuagu/shanpo6.c
# // Last Modified by Winder on Mar. 5 2001
# inherit ROOM;

# #include <ansi.h>
# #include "yangfeng.h";
extends Room
# var __DIR__ = "/d/baihuagu/"

func create():
	set("short", GRN + "山谷中" + NOR);
	set("long",
HIY + """这是一面山谷。由于山坡向南，阻住了山风，加之地下矿藏
丰富，所以地气极暖，百花先放。此处架着几个木架，托着七八
个蜂巢。但见群蜂争舞，到处都是嗡嗡声，给静谧的山谷带来了
无限生气。山谷中高树林立，还有很多灌木，想来谷中物产极多，
偶尔可见一两个挖掘草药的农人。\n""" + NOR);
	set("outdoors", "baihuagu");
	set("count", 10);
	set("exits", {
		"westup" : __DIR__ + "baihuagu2",
	});
	set("objects", {
		__DIR__ + "npc/yubee": 2
	});
	set("item_desc", {
		"蜂巢" : "这是一个巨大的蜂巢，里面很多密蜂正忙着酿蜜。\n",
	});
	set("coor/x", -390);
	set("coor/y", -370);
	set("coor/z", -10);
	setup();

func _init():
	create()
	init()	

func init():
	add_action("do_dig","dig");
	add_action("do_full","full");
	add_action("do_yang","yang");
	add_action("do_getmi","getmi");

func do_dig():
	var me;
	var food;
	me=this_player();
	if( me.query("food") >= me.max_food_capacity() ):
		message_vision( HIC + "$N正要挖什么，突然老顽童跑了过来，邪恶地笑了一下，猛然从身后取出一支茯苓，望$N嘴中灌过去，口中叫道：我叫你吃！！把$N灌得头晕眼花，吃的都吐了出来。老顽童得意地笑了，又一溜烟地跑了。\n" + NOR,me);
	else:
		if (query("count") > 0):
			message_vision("$N挖了一会儿，挖到一颗首乌。当下坐下，吃将起来。\n",me);
			me.add("food", 30);
			add("count", -1);
		else :
			message_vision("$N挖了一会儿，啥都没有。\n",me);

func do_full():
	var me;
	me=this_player();
	if( me.query("water") >= me.max_water_capacity() ):
		message_vision( HIY + "$N意犹未尽地拍了拍肚子，手伸向蜂巢——突然惨叫一声，整个人都跳了起来，只见整只手都膨胀起来。\n" + NOR,me);
		return 1;
	else:
		if (query("count") > 0):
			message_vision("$N从蜂巢中取了些蜂浆，喝了起来。\n",me);
			me.add("water", 30);
			add("count", -1);
		else :
			message_vision("$N掏了一会儿，啥都没有。\n",me);

func do_getmi():
	var me;
	me=this_player();
	if (me.query_temp("marks/getmi")):
		message_vision(HIY + "$N欢叫一声，从蜂巢中取出一罐蜜。\n" + NOR,me);
		new_ob("/d/baihuagu/obj/mi").move(me);
		me.set_temp("marks/getmi",0);
	else:
		message_vision( HIR + "$N嘿嘿一笑，贼忒兮兮地向蜂巢凑去，正要有所行动，突听嗡的几声，几只玉蜂从里面冲将而出，把$N蜇得满头大包！\n" + NOR,me);
