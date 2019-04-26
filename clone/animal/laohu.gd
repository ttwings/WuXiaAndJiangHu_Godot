# laohu.c 老虎
# Last Modified by winder on Aug. 1 2002

# extends Npc_TRAINEE;
# inherit "/# inherit/char/trainee";

func create():

	set_name("老虎", ["lao hu", "hu", "tiger"]);
	set("race", "走兽");
	set("age", 25);
	set("long", "这是一头吊睛白额，气势汹汹的大虎，正恶狠狠地盯着你，好象随时随地都会扑上来择人而噬！\n");
	set("msg_fail", "$n冲$N呲牙吼了一声");
	set("msg_succ", "$n一面口中向$N荷荷发威，一面向后退了半步，似乎有些怯了");
	set("msg_trained", "$n低吼着在$N的面前伏了下来");
	set("auto_follow", 1);
	set("attitude", "aggressive");

	set("wildness", 12);
	set("ridable", 1);
	set("ability", 4);

	set("str", 40);
	set("con", 40);
	set("dex", 40);
	set("int", 10);

	set("combat_exp", 20000);

	set_temp("apply/attack", 50);
	set_temp("apply/damage", 70);
	set_temp("apply/armor", 30);

	set_weight(150000);

	set("chat_chance", 10);
	set("chat_msg", [
						(
							: this_object(), "random_move"
							:),
						"老虎用前爪拍击着地面，口中荷荷发威，好象随时都要扑上来！\n",
						"老虎微微侧着脑袋，双目炯炯，紧紧地注视着你的一举一动。\n",
						"老虎突然立了起来，绕着你走了半圈，似乎在观察着什么。\n",
					]);

	set("chat_msg_combat", [
							   (
								   : this_object(), "random_move"
								   :),
							   "\n老虎怒啸一声，一反身，长长的尾巴向铁棍一样挥了过来！\n",
							   "\n老虎全身一曲一弓，忽然跃起半空，猛地扑了下来！\n",
						   ]);

	setup();


func die():

	message_vision("\n$N仰天惨嚎了一声，趴在地上不动了。\n", this_object());
	::die();


func _init():

	var ob;

	::init();
	if (interactive(ob = this_player()) && ob.query_weight() >= 50000):
	
		if (!this_object().query_lord(ob)):
		
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob);
		
	

