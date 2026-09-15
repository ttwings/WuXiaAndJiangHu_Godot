# yetu.c 野兔
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("野兔", ["ye tu", "ye", "hare"]);
	set_attr("race", "走畜");
	set_attr("age", 5);
	set_attr("long", "一只好可爱的小野兔。\n");
	set_attr("attitude", "peaceful");

	set_attr("combat_exp", 50);

	set_temp("apply/attack", 2);
	set_temp("apply/defense", 5);
	set_temp("apply/damage", 2);
	set_temp("apply/armor", 1);

	setup();


func die():

	var ob;
	message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
	ob = new (__DIR__ +  "obj/turou");
	ob.move(environment(this_object()));
	destruct(this_object());

