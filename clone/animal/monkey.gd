# monkey.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("猴子", ["monkey"]);
	set_attr("gender", "雄性");
	set_attr("race", "走兽");
	set_attr("age", 25);
	set_attr("long", "这只猴子在在桃树间跳上跳下，还不时津津有味地啃几口着蜜桃。\n");
	set_attr("combat_exp", 5000);
	set_attr("attitude", "peaceful");

	set_attr("water", 200);
	set_attr("food", 200);

	set_attr("apply/attack", 10);
	set_attr("apply/defense", 10);

	#	set_attr("chat_chance", 30);
	#	set_attr("chat_msg", [
	#		"土匪一声大喊: 此山是我开，此树是我栽，若要从此过，留下买路财 !\n",
	#	] );

	set_skill("unarmed", 25);
	set_skill("parry", 20);
	set_skill("dodge", 20);

	setup();

