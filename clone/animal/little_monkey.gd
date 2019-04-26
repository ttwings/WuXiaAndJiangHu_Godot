# little_monkey.c
# Last Modified by winder on Aug. 1 2002

extends Npc;

func create():

	set_name("小猴", ["little monkey", "monkey"]);
	set("race", "走兽");
	set("gender", "雄性");
	set("age", 7);
	set("long", "这是一只调皮的小猴子，虽是畜牲，却喜欢模仿人样。\n");
	set("combat_exp", 50);
	set("shen_type", -1);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
	set("attitude", "peaceful");
	setup();
	carry_object("/d/wudang/obj/greyrobe").wear();

