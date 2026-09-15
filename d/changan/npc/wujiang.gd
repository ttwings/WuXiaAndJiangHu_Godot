# // wujiang.c 武将

# inherit NPC;
# //inherit F_SKILL;
extends Npc
func create():
	set_name("武将", "wu jiang");
	set_attr("gender", "男性");
	set_attr("age", random(10) + 30);
	set_attr("str", 25);
	set_attr("dex", 16);
	set_attr("long", "他站在那里，的确有说不出的威风。\n");
	set_attr("combat_exp", 75000);
	set_attr("shen_type", 1);
	set_attr("attitude", "peaceful");

	set_skill("unarmed", 60);
	set_skill("force", 60);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set_attr("neili", 400); 
	set_attr("max_neili", 400);
	set_attr("jiali", 10);

	setup();
	# carry_object(__DIR__"obj/gangjian").wield();
	# carry_object(__DIR__"obj/tiejia").wear();

# func init()
# {
# 	object ob;
# 	::init();
# 	if (interactive(ob = this_player()) && 
# 		(int)ob->query_condition("killer")) {
# 		remove_call_out("kill_ob");
# 		call_out("kill_ob", 1, ob);
