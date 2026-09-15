# dog.c
# Last Modified by winder on Aug. 1 2002

# extends Npc_TRAINEE;
# inherit "/# inherit/char/trainee";

func create():

	set_name("野狗", ["dog"]);
	set_attr("race", "走畜");
	set_attr("age", 3);
	set_attr("long", "一只浑身脏兮兮的野狗。\n");

	set_attr("str", 32);
	set_attr("dex", 36);

	set_attr("chat_chance", 6);
	set_attr("chat_msg", [(
						  : this_object(), "random_move"
						  :),
					  "野狗用鼻子闻了闻你的脚。\n",
					  "野狗在你的脚边挨挨擦擦的，想讨东西吃。\n",
					  "野狗对著你摇了摇尾巴。\n",
					  "野狗用後腿抓了抓自己的耳朵。\n"]);

	set_temp("apply/attack", 10);
	set_temp("apply/armor", 3);

	setup();


func accept_object(who, ob):

	if (ob.id("bone")):
	
		set_leader(who);
		message("vision", name() + "高兴地汪汪叫了起来。\n", environment());
		return 1;
	

