# /clone/beast/xbaozi.c 小豹子
# Last Modified by winder on Aug. 1 2002

#include <ansi.h>
extends Npc;

func create():

	set_name("小豹子", ["xiao baozi", "baozi"]);
	set_attr("race", "走兽");
	set_attr("age", 1);
	set_attr("long", "一只身体不大可是很结实的小豹子，它正瞪着眼睛看着你。\n");
	set_attr("attitude", "aggressive");
	set_weight(200000);
	set_attr("max_qi", 100);
	set_attr("max_jing", 100);
	set_attr("max_jingli", 100);

	set_attr("str", 30);
	set_attr("con", 80);
	set_attr("dex", 30);
	set_attr("int", 10);

	set_attr("combat_exp", 20000);

	set_temp("apply/attack", 10);
	set_temp("apply/damage", 10);
	set_temp("apply/armor", 10);

	setup();


func die():

	var ob
	var ob2 = this_object();

	ob = new (__DIR__ +  "obj/baodan");
	ob.move(environment(this_object()));
	message_vision("$N惨嚎一声，死了！\n", this_object());
	destruct(ob2);

