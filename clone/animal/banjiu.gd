# banjiu.c 斑鸠
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("斑鸠", ["ban jiu", "bird"]);
	set_attr("race", "飞禽");
	set_attr("age", 2);
	set_attr("long", "一只的小斑鸠。\n");
	set_attr("attitude", "peaceful");

	set_attr("combat_exp", 100);

	set_temp("apply/attack", 2);
	set_temp("apply/defense", 6);
	set_temp("apply/damage", 1);
	set_temp("apply/armor", 1);

	setup();


func die():

	ob = new (__DIR__ +  "obj/banjiu-rou");

	message_vision("$N从半空中栽了下来，死了。\n", this_object());
	ob.move(environment(this_object()));
	destruct(this_object());

