// Last Modified by sir 2003.11.14
#include <ansi.h>
inherit NPC;

int do_back(object me);

void create()
{
	//	set_name("黑衣人", ({ "heiyi ren","ren"}));
	NAME_D->generate_cn_name(this_object());
	set("gender", "男性");
	set("quest_no_guard", 1);
	set("no_steal", 1);
	set("no_ansuan", 1);
	//	set("long", "一个穿着黑色夜行衣的人。\n");
	set("chat_chance", 10);
	set("chat_msg", ({(
						: random_move:)}));
	set("chat_chance_combat", 80);
	set("quest", "kill");
	set("chat_msg_combat", ({
							   (
								   : exert_function, "recover"
								   :),
							   (
								   : exert_function, "powerup"
								   :),
						   }));
	setup();
	add_money("silver", 10 + random(30));
	carry_object("/d/city/obj/tiejia")->wear();
	if (clonep())
		call_out("do_back", 943, this_object()); //四天内4*(86400/365)-1
}

int do_back(object me)
{
	if (me->is_fighting())
	{
		call_out("do_back", 200, this_object());
		return 1;
	}
	if (objectp(environment(me)))
	{
		tell_room(environment(me), me->query("name") + "匆匆忙忙的离开了。\n", ({me}));
		destruct(me);
	}
	return 1;
}

void die()
{
	object ob = this_object();
	object me, fme;
	object *obs;
	int pot, exp, level, score;
	int all_exp, all_pot, all_score;
	int per_exp, per_pot, per_score;
	int i;
	int lvl;
	mapping q;
	int quest_count;
	int added;
	int quest_level;

	me = find_player(ob->query("owner"));
	if (!objectp(me))
		return ::die();
	q = me->query("quest/kill"); //任务相关
	q["notice"] = "die";
	lvl = NPC_D->check_level(me);
	exp = 10 + random(5) + lvl;
	pot = 5 + random(3) + lvl;
	score = 2 + random(3) + lvl / 2;

	quest_count = me->query("quest_num/kill") + 1;
	if (quest_count >= 500)
	{
		// 连续完成了超过500次的任务
		exp += 80 + random(quest_count / 20 + 1);
		pot += 45 + random(quest_count / 25 + 1);
		score += 4 + random(15);
	}
	else if (quest_count >= 200)
	{
		// 连续完成了超过200次的任务
		exp += 70 + random(quest_count / 20 + 1);
		pot += 40 + random(quest_count / 25 + 1);
		score += 3 + random(10);
	}
	else if (quest_count >= 100)
	{
		// 连续完成了超过100次的任务
		exp += 50 + random(quest_count / 20 + 1);
		pot += 30 + random(quest_count / 25 + 1);
		score += 2 + random(10);
	}
	else if (quest_count >= 10)
	{
		// 连续完成了超过10次的任务
		exp += 45 + random(quest_count / 20 + 1);
		pot += 25 + random(quest_count / 25 + 1);
		score += 1 + random(5);
	}
	switch (quest_level = q["level"])
	{
	case 0:
		exp = exp / 2 + 1;
		pot = pot / 2 + 1;
		score = score / 4 + 1;
		break;
	case 1:
		break;
	case 2:
		exp += exp / 4;
		pot += pot / 4;
		score += score / 4;
		break;
	case 3:
		exp += exp / 2;
		pot += pot / 2;
		score += score / 2;
		break;
	}
	quest_level = q["level"];
	quest_level++;
	if (quest_level > 3)
		quest_level = 1;
	me->set("quest_num/kill", quest_count);
	me->add("quest_num/allkill", 1);
	me->set_temp("quest/next_level", quest_level);
	if ((added = (int)me->query_temp("quest/help_count")) > 0)
	{
		me->delete_temp("quest/help_count");
	}
	added += (int)me->query_temp("quest/escape_times") * 2;
	me->delete_temp("quest/escape_times");
	// 根据NPC的帮手和逃走的次数调整经验
	if (added)
	{
		exp += exp * added / 2;
		pot += pot * added / 2;
	}
	//        me->delete("quest/kill");
	// 这里调整一些 以上比例是2:1左右
	// 每个下来是200多exp 100多pot
	exp *= 3;
	pot *= 2;
	score *= 2;
	// end
	all_exp = exp;
	all_pot = pot;
	all_score = score;

	obs = ob->query_temp("killer");
	if (!sizeof(obs))
		return ::die();

	fme = ob->query_temp("faint_by");

	per_exp = all_exp / (sizeof(obs) + 1 + objectp(fme));
	per_pot = all_pot / (sizeof(obs) + 1 + objectp(fme));
	per_score = all_score / (sizeof(obs) + 1 + objectp(fme));
	q["helper"] = obs;
	for (i = 0; i < sizeof(obs); i++)
	{
		if (objectp(obs[i]) && environment(obs[i]) == environment(ob))
		{
			exp = per_exp;
			pot = per_pot;
			score = per_score;
			if (obs[i] == fme) //打晕的双份
			{
				exp += per_exp;
				pot += per_pot;
				score += per_score;
			}
			if (obs[i] == me) // 领任务的双份
			{
				exp += per_exp;
				pot += per_pot;
				score += per_score;
				obs[i]->set_temp("quest_kill/combat_exp", exp);
				obs[i]->set_temp("quest_kill/potential", pot);
				obs[i]->set_temp("quest_kill/score", score);
			}
			else
			{
				obs[i]->add("combat_exp", exp);
				obs[i]->add("potential", pot);
				obs[i]->add("score", score);
				//			obs[i]->set_temp("prize_reason","追杀");
				//			obs[i]->set_temp("can_give_prize",1);
				//			obs[i]->set_temp("prize_exp",exp);
				//			obs[i]->set_temp("prize_pot",pot);

				tell_object(obs[i], HIW "经过这番历练，你被奖励了：");
				tell_object(obs[i], chinese_number(exp) + "点实战经验、" +
										chinese_number(pot) + "点潜能、" +
										chinese_number(score) + "点江湖阅历。\n" NOR);
			}
		}
	}

	::die();
}

int accept_fight(object ob)
{
	object *killer;

	killer = this_object()->query_temp("killer");
	if (!arrayp(killer))
		killer = ({});
	if (member_array(ob, killer) < 0)
		killer += ({ob});
	this_object()->set_temp("killer", killer);
	command("say 好！咱们就比划比划！");
	kill_ob(ob);
	return 1;
}

int accept_hit(object ob)
{
	object *killer;

	killer = this_object()->query_temp("killer");
	if (!arrayp(killer))
		killer = ({});
	if (member_array(ob, killer) < 0)
		killer += ({ob});
	this_object()->set_temp("killer", killer);
	command("say 你死去吧！");
	kill_ob(ob);
	return 1;
}

int accept_kill(object ob)
{
	object *killer;

	killer = this_object()->query_temp("killer");
	if (!arrayp(killer))
		killer = ({});
	if (member_array(ob, killer) < 0)
		killer += ({ob});
	this_object()->set_temp("killer", killer);
	this_object()->set_temp("killer", killer);
	command("say 哼！找死！");
	return 1;
}
int accept_ansuan(object who) { return notify_fail("此人警惕性太高，没法暗算。\n"); }
int accept_touxi(object who) { return accept_kill(who); }
void random_move()
{
	NPC_D->random_move(this_object());
}