// Last Modified by winder on Apr. 25 2001
// pker.c

#include <ansi.h>
inherit NPC;
void create()
{
	set("level", 0);
	set_name("七杀门杀手", ({"sha shou", "sha", "shou"}));
	set("gender", "男性");
	set("age", 30);
	set("long", "他是七杀门的杀手。\n");
	set("per", 10);
	set("attitude", "peaceful");

	set("str", 15);
	set("int", 35);
	set("con", 35);
	set("dex", 35);

	set("min_kill_exp", 1000);
	set("qi", 2000);
	set("max_qi", 2000);
	set("jing", 2000);
	set("max_jing", 2000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 40);
	set("combat_exp", 1000000);
	set("score", 0);
	set("shen_type", 0);

	set("base_level", 200);
	set("special_level", 200);
	//  call_out("setskill",0);//set skill
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
														 (
																 : exert_function, "recover"
																 :),
														 (
																 : perform_action, "sword.chan"
																 :),
														 (
																 : perform_action, "sword.lian"
																 :),
														 (
																 : perform_action, "sword.sui"
																 :),
												 }));
	set("chat_chance", 10);
	set("chat_msg", ({
											(
													: call_out, "random_move", 0
													:),
									}));
	set("haojie", 1);
	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob;
	if (interactive(ob = this_player()))
	{
		remove_call_out("killing");
		call_out("killing", 0, ob);
	}
}

void killing(object ob)
{
	int player_exp, exp, min;
	exp = (int)this_object()->query("combat_exp", 1);
	player_exp = (int)ob->query("combat_exp", 1);
	//        min=(int)exp-5000;
	if (environment(this_object()) != environment(ob))
		return;
	if (player_exp <= 2000)
		return;
	if (player_exp >= query("min_kill_exp"))
	{
		message_vision("$N对著$n喝道：「" + RANK_D->query_rude(ob) + "！今天不是你死就是我亡！」\n", this_object(), ob);
		this_object()->kill_ob(ob);
	}
	return;
}

void die()
{
	object ob = this_object();
	object me, sword;
	int pot, exp, level, score;
	int myexp, obexp;
	if (me = query_temp("last_damage_from"))
	{
		level = ob->query("level");
		pot = level * 10;
		exp = level * 50;
		score = level * 10;
		myexp = me->query("combat_exp");
		obexp = ob->query("combat_exp");
		if (myexp > 10000 &&
				myexp > obexp - obexp / 5 &&
				myexp < obexp + obexp / 5)
		{
			pot *= 3;
			exp *= 3;
		}
		me->add("combat_exp", exp);
		me->add("potential", pot);
		me->add("score", score);
		me->add_temp("hj_killer", 1);
		message_vision("$N咬牙切齿地对着天空大叫：“贼老天！”\n", ob);
		tell_object(me, HIW "你杀敌有功，得到如下奖励：\n");
		tell_object(me, chinese_number(exp) + "点实战经验\n" +
												chinese_number(pot) + "点潜能\n" +
												chinese_number(score) + "点江湖阅历\n" NOR);
	}
	if (sword = present("long sword", environment(ob)))
		destruct(sword);
	destruct(ob);
}

int random_move()
{
	mapping exits;
	string *dirs, dir, dest;

	if (!mapp(exits = environment()->query("exits")))
		return 0;
	dirs = keys(exits);
	dir = dirs[random(sizeof(dirs))];
	dest = exits[dir];
	//  if( domain_file(dest)!=query("domain") ) return 0;
	if (find_object(dest)->query("no_fight"))
		return 0;
	if (this_object()->is_fighting())
		return 0;
	command("go " + dir);
	return 1;
}
