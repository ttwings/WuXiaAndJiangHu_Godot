# /*  <SecCrypt CPL V3R05>  */
 
# inherit  NPC;
extends Npc
func create():
	set_name("酸秀才", "suan  xiucai");
	set_attr("age",  22);
	set_attr("gender",  "男性");
	set_attr("long", "落榜秀才，颇觉得有些怀才不遇。\n");
	set_attr("attitude",  "peaceful");
	set_attr("per",  22);
	set_attr("combat_exp",  8000);
	set_attr("shen_type",  1);
	# class change to class_
	set_attr("class_", "scholar");
	set_attr("force",  200);
	set_attr("max_force",  200);
	set_attr("force_factor",  3);
	set_skill("unarmed",  40);
	set_skill("dodge",  40);
	set_skill("parry",  40);
	setup();

	carry_object("/clone/misc/cloth")->wear();

