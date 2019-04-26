# laoshu.c 老鼠
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("老鼠", ["lao shu", "shu", "mouse"]);
	set("race", "走兽");
	set("age", 2);
	set("long", "一只赃兮兮的小老鼠。\n");
	set("attitude", "peaceful");

	set_weight(300);

	set("combat_exp", 100);
	set("env/wimpy", 70);

	set_temp("apply/attack", 5);
	#	set_temp("apply/damage", 20);
	set_temp("apply/dodge", 20);
	set_temp("apply/armor", 1);

	setup();


func die():

	var ob;
	message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
	ob = new (__DIR__ +  "obj/shurou");
	ob.move(environment(this_object()));
	destruct(this_object());

