# // zhu.c 朱熹

# inherit NPC;
#include <ansi.h>
extends Npc
func create():
	set_name("冯从吾", ({ "feng congwu", "feng" }));
	set("long",
"冯先生是当代大学者，精通儒术。\n");
	set("gender", "男性");
	set("age", 65);
	set("no_get", 1);
	set_skill("literate", 300);

	set_skill("unarmed", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_temp("apply/attack", 80);
	set_temp("apply/defense", 80);
	set_temp("apply/damage", 20);

	set("combat_exp", 400000);
	set("shen_type", 1);
	setup();

func recognize_apprentice(ob):
	if ob.query_temp("mark/冯") ==  false :
		return 0;
	ob.add_temp("mark/冯", -1);
	return 1;

func accept_object(who,ob):
	var me = this_player();
	if (!who.query_temp("mark/冯")):
		who.set_temp("mark/冯", 0);
	if (ob.query("money_id") && ob.value() >= 1000) :
		message_vision("冯从吾同意指点$N一些读书写字的问题。\n", who);
		who.add_temp("mark/冯", ob.value() / 50);
		return 1;