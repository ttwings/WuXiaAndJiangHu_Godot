# laoshu.c 老鼠
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():
{
	set_name("老鼠", ["lao shu", "shu", "mouse"]);
	set_attr("race", "走兽");
	set_attr("age", 2);
	set_attr("long", "一只赃兮兮的小老鼠。\n");
	set_attr("attitude", "peaceful");

	set_weight(300);

	set_attr("combat_exp", 100);
	set_attr("env/wimpy", 70);

	set_temp("apply/attack", 5);
	#	set_temp("apply/damage", 20);
	set_temp("apply/dodge", 20);
	set_temp("apply/armor", 1);

	setup();
}

func die()
{
	ob;
	message_vision("$N凄惨的嚎了几声，死了。\n", this_object());
	ob = new (__DIR__ +  "obj/shurou");
	ob.move(environment(this_object()));
	destruct(this_object());
}
