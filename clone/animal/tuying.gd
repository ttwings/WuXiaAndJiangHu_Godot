# tuying.c
# Last Modified by winder on Aug. 1 2002

# extends Npc_TRAINEE;
# inherit "/# inherit/char/trainee";

func create():

	set_name("秃鹰", ["eagle", "ying", "tuying"]);
	set_attr("race", "飞禽");
	set_attr("age", 15);
	set_attr("long", "一只生活在高原上，黑色的秃鹰，一身乱蓬蓬的羽毛，凶悍丑陋。\n");
	set_attr("attitude", "aggressive");
	set_attr("wildness", 9);
	set_attr("msg_fail", "$n一惊对着$N就啄，$N忙缩回手");
	set_attr("msg_succ", "$N一挥手，$n轻轻扑腾了几下翅膀");
	set_attr("msg_trained", "$n飞了起来轻轻停到$N的肩上");
	set_attr("auto_follow", 1);

	set_attr("str", 29);
	set_attr("con", 40);
	set_attr("dex", 45);
	set_attr("int", 10);

	set_attr("combat_exp", 12000);
	set_temp("apply/attack", 30);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 10);

	setup();

	set_attr("chat_chance", 7);
	set_attr("chat_msg", [
						"「嘎~~嘎~~」秃鹰发出几声凄厉的哀叫。\n",
						"秃鹰突然从高空盘旋着朝你俯冲下来，停落在你不远处。\n",
						"秃鹰犹犹豫豫地来回走着，贪婪的眼睛狠狠地盯着你。\n",
						"秃鹰扑腾了几下翅膀。\n",
					]);

func _init():

	var ob;
	::init();
	if (interactive(ob = this_player()) && this_object().query_lord() != ob && random(ob.query_kar() + ob.query_per()) < 5):
	
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	

