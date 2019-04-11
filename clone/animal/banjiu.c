// banjiu.c 斑鸠
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
	set_name("斑鸠", ({ "ban jiu", "bird"}) );
	set("race", "飞禽");
	set("age", 2);
	set("long", "一只的小斑鸠。\n");
	set("attitude", "peaceful");
	
	set("combat_exp", 100);

	set_temp("apply/attack", 2);
	set_temp("apply/defense", 6);
	set_temp("apply/damage", 1);
	set_temp("apply/armor", 1);

	setup();
}

void die()
{
	object ob = new(__DIR__"obj/banjiu-rou");

	message_vision("$N从半空中栽了下来，死了。\n", this_object());
	ob->move(environment(this_object()));
	destruct(this_object());
}

