# laohu.c 狮子
# Last Modified by winder on Aug. 1 2002

# extends Npc_TRAINEE;
# inherit "/# inherit/char/trainee";

func create():

	set_name("狮子", ["lion", "shi zi", "shi"]);
	set_attr("race", "走兽");
	set_attr("age", 25);
	set_attr("long", "一只黄毛长鬃的雄狮，爪牙锐利，神情威武。\n");
	set_attr("msg_fail", "$n冲$N呲牙吼了一声");
	set_attr("msg_succ", "$n一面口中向$N荷荷发威，一面向后退了半步，似乎有些怯了");
	set_attr("msg_trained", "$n低吼着在$N的面前伏了下来");
	set_attr("auto_follow", 1);
	set_attr("attitude", "aggressive");

	set_attr("wildness", 12);
	set_attr("ridable", 1);
	set_attr("ability", 4);

	set_attr("str", 40);
	set_attr("con", 40);
	set_attr("dex", 40);
	set_attr("int", 10);

	set_attr("combat_exp", 20000);

	set_temp("apply/attack", 50);
	set_temp("apply/damage", 70);
	set_temp("apply/armor", 30);

	set_weight(150000);

	set_attr("chat_chance", 10);
	set_attr("chat_msg", [
						(
							: this_object(), "random_move"
							:),
						"狮子来回走动，朝着你端相了半晌，口中荷荷的发威。\n",
						"狮子长长吼了一声。\n",
						"狮子趴在地上，摆头抖了抖鬃毛，一双眼睛紧紧盯着你。\n",
					]);

	setup();


func die():

	message_vision("\n$N仰天惨嚎了一声，趴在地上不动了。\n", this_object());
	::die();


func _init():

	var ob;

	::init();
	if (interactive(ob = this_player()) && ob.query_weight() >= 50000)
	
		if (!this_object().query_lord(ob))
		
			remove_call_out("kill_ob");
			call_out("kill_ob", 1, ob);
		
	

	#      add_action("do_ride", "ride");
	#      add_action("do_unride", "unride");
	add_action("do_look", "look");


func do_look(arg):

	object *inv;
	var i;

	inv = all_inventory(this_object());

	if (!id(arg)):
		return 0;

	if (!sizeof(inv)):
		return 0;

	printf(this_object().query("long") +COMBAT_D.eff_status_msg(this_object().query("eff_qi") * 100 / this_object().query("max_qi")) + "\n" + "它身上驮着：\n");
	for (i = 0; i < sizeof(inv); i++)
		printf("%s \n", inv[i].short());
	return 1;

