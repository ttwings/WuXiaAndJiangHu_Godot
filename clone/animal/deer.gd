# deer.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("梅花鹿", ["deer"]);
	set_attr("race", "走畜");
	set_attr("age", 5);
	set_attr("long", "一只漂亮的梅花鹿。\n");
	set_attr("attitude", "peaceful");

	set_attr("combat_exp", 800);

	set_attr("chat_chance", 6);
	set_attr("chat_msg_combat", ["\n梅花鹿一转身，扬起鹿角朝你顶过来！\n",]);

	set_temp("apply/attack", 20);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 10);
	set_temp("apply/armor", 10);

	setup();

