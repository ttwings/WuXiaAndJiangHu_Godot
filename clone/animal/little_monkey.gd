# little_monkey.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("小猴", ["little monkey", "monkey"]);
	set_attr("race", "走兽");
	set_attr("gender", "雄性");
	set_attr("age", 7);
	set_attr("long", "这是一只调皮的小猴子，虽是畜牲，却喜欢模仿人样。\n");
	set_attr("combat_exp", 50);
	set_attr("shen_type", -1);
	set_attr("str", 11);
	set_attr("dex", 11);
	set_attr("con", 11);
	set_attr("int", 11);
	set_attr("attitude", "peaceful");
	setup();
	carry_object("/d/wudang/obj/greyrobe").wear();

