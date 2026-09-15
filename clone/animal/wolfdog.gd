# wolfdog.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("大狼狗", ["wolf dog", "dog"]);
	set_attr("race", "走兽");
	set_attr("age", 4);
	set_attr("long", "一只昂首挺胸，吐着长舌头的大狼狗。像是财主家里养的宠物。\n");
	set_attr("attitude", "peaceful");

	set_attr("str", 26);
	set_attr("cor", 30);

	set_attr("combat_exp", 1000);

	set_attr("chat_msg_combat", [(
								 : this_object(), "random_move"
								 :),
							 "大狼狗大声吠叫：汪！汪！汪！汪！汪！汪！\n",
							 "大狼狗突然跳了起来，口中乱咬，却不知道是在咬谁。\n"]);

	set_temp("apply/attack", 15);
	set_temp("apply/damage", 6);
	set_temp("apply/armor", 2);

	setup();


func _init():

	var ob = this_player();
	::init();
	if (interactive(ob) &&
		!environment().query("no_fight") &&
		random(ob.query_kar() + ob.query_per()) < 30)
	
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	


func die():

	var ob;
	ob = new (__DIR__ +  "obj/goupi");
	ob.move(environment(this_object()));
	destruct(this_object());

