// feizei.c
//last modified by sir 4.21.2002

#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;
inherit F_UNIQUE;
int set_perform();

void create()
{
	set_name("飞贼", ({"fei zei", "fei", "zei"}));
	set("title", HIY "飞天遁地" NOR);
	set("age", 30 + random(20));
	set("long",
		"这是无恶不做的飞贼，背上有一个小小包裹，看样子是才偷了什么东西在手。\n");
	set("int", 30);
	set("str", 20 + random(10));
	set("con", 30);
	set("dex", 80 + random(30));
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("no_get", 1);
	set("max_qi", 2500 + random(500));
	set("max_jing", 1200 + random(300));
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 50 + random(80));
	set("combat_exp", 500000);
	set("score", 15000);
	set_temp("apply/attack", 60);
	set_temp("apply/defense", 60);
	set_temp("apply/damage", 40);

	set("str_lvl", 1);
	set("attitude", "friendly");
	set("chat_chance", 30);
	set("chat_msg", ({
						(
							: call_out, "random_move", 0
							:),
					}));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("gold", 1);
}
void init()
{
	object ob, me, money;
	int i;
	object *inv;
	if (!query("inited"))
	{
		set("inited", 1);
		set_perform();
	}
	ob = this_player();
	if (!interactive(ob))
		return;
	if (!living(ob) || ob->query_temp("noliving"))
		return;
	if (ob->query_temp("ride_horse"))
		return;
	if (random(5) > 1)
	{
		me = this_object();
		command("heihei " + ob->query("id"));
		if (money = present("gold_money", ob))
		{
			//destruct(money);
			tell_object(ob, HIR "你突然发现身上的" + money->query("name") + HIR + "不见了！\n" NOR);
			if (!money->move(this_object()))
				destruct(money);
		}
		else if (money = present("silver_money", ob))
		{
			//destruct(money);
			tell_object(ob, HIR "你突然发现身上的" + money->query("name") + HIR + "不见了！\n" NOR);
			if (!money->move(this_object()))
				destruct(money);
		}
		//			else if(money = present("budai",ob))
		//			{
		//				tell_object(ob, HIR "你突然发现身上的"+money->query("name")+HIR+"不见了！\n"NOR);
		//				if (!money->move(this_object())) destruct(money);
		//			}
		else
		{
			inv = all_inventory(ob);
			for (i = 0; i < sizeof(inv); i++)
			{
				if ((inv[i]->is_container()) || (inv[i]->is_unique() && !inv[i]->query("equipped")))
				{
					tell_object(ob, HIR "你突然发现身上的" + inv[i]->query("name") + HIR + "不见了！\n" NOR);
					if (!inv[i]->move(this_object()))
						destruct(inv[i]);
					break;
				}
			}
			if (i == sizeof(inv))
			{
				command("say 你这个穷光蛋，连点油水都没有，给我滚！");
				if (!ob->is_busy())
					ob->start_busy(1);
			}
		}
		command("kick " + ob->query("id"));
	}

	//		add_action("do_hit","hit");
	//		add_action("do_hit","kill");
	add_action("do_halt", "halt");
	add_action("do_halt", "surrender");
}
int set_perform()
{
	object ob = this_object();

	NPC_D->set_perform(ob);
	ob->set("chat_chance_combat", 40);
	return 1;
}
int accept_hit(object me)
{
	object ob = this_object();

	if ((int)me->query("combat_exp") > (int)ob->query("combat_exp"))
		ob->set("combat_exp", (int)me->query("combat_exp"));
	ob->fight_ob(me);
	if (living(ob) && !ob->query_temp("noliving") && !ob->is_busy() && userp(me))
		ob->set_temp("enemy/" + me->query("id"), 1);
	return 1;
}
int accept_fight(object who) { return accept_hit(who); }
int accept_kill(object who) { return accept_hit(who); }
int accept_ansuan(object who) { return accept_hit(who); }
int accept_touxi(object who) { return accept_hit(who); }
void random_move()
{
	return NPC_D->random_move(this_object());
}
int do_halt()
{
	object me = this_player();
	object ob = this_object();

	if (me->is_fighting(ob))
	{
		message_vision(HIW "$N喝道：“既然被你看出身份，就休想活着离开！”\n" NOR, ob, me);
		return 1;
	}
	return 0;
}
void die()
{
	object ob = this_object();
	object me, fme;
	int pot, exp, level, score;
	int flag, i;
	string *enemys;
	object who;

	me = ob->query_temp("last_damage_from");
	fme = ob->query_temp("last_opponent");
	if (!objectp(me) || !userp(me)) //如果是npc打死 或者意外死亡
	{
		if (!ob->query_temp("enemy"))
			return ::die();
		enemys = keys(ob->query_temp("enemy"));
		flag = 1;
		for (i = 0; i < sizeof(enemys); i++)
		{
			if (!objectp(who = present(enemys[i], environment(ob))) || !userp(who))
				continue;
			if (who->is_fighting(ob))
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return ::die();
		//        	else return; //如果环境中还有玩家敌人 那么将不会被npc打死
	}
	else
	{
		if (!ob->query_temp("enemy/" + me->query("id")))
			return ::die();
		level = ob->query("str_lvl");
		pot = level * 100;
		exp = level * 350;
		score = 300 + random(50);
		me->add("combat_exp", exp);
		me->add("potential", pot);
		me->add("score", score);
		message_vision("$N咬牙切齿地对着天空大叫：“贼老天！”\n", ob);
		tell_object(me, HIW "你杀敌有功，得到如下奖励：\n");
		tell_object(me, chinese_number(exp) + "点实战经验\n" +
							chinese_number(pot) + "点潜能\n" +
							chinese_number(score) + "点江湖阅历\n" NOR);
		return ::die();
	}
}
