// /clone/quest/questjianxi.c
//last modified by sega 13/4/2000
// Modified by Zeratul Jan 5 2001

//修改成不能帮忙杀
#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string *name_msg = ({
		"流氓",
		"进香客",
		"挑夫",
		"家丁",
		"官兵",
		"卖花姑娘",
		"趟子手",
		"小贩",
		"刀客",
		"剑客",
		"游方和尚",
		"江湖豪客",
});

string *long_id = ({
		"liu mang",
		"jinxiang ke",
		"tiao fu",
		"jia ding",
		"guan bing",
		"flower girl",
		"tangzi shou",
		"xiao fan",
		"dao ke",
		"jian ke",
		"seng ren",
		"jianghu haoke",
});

void create()
{
	int i;
	i = random(sizeof(name_msg));
	set_name(name_msg[i], ({long_id[i]}));
	set("gender", random(2) > 0 ? "女性" : "男性");
	set("attitude", "friendly");
	set("chat_chance", 30);
	set("chat_msg", ({
											(
													: call_out, "random_move", 0
													:),
									}));
	set("inquiry", ([
												"奸细":(
																	 : ask_me:),
										 "jian xi":(
																	 : ask_me:),
											"jianxi":(
																	 : ask_me:),
	]));
	set("no_steal", 1);
	//      set("ask_time", 0);
	set("jianxi", 1);
	setup();
	carry_object("/d/city/npc/obj/tiejia")->wear();
	//	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/food/jiudai");
	if (clonep())
		call_out("dest_me", 1200, this_object());
}
int ask_me(object who)
{
	object ob = this_object(), me = this_player();
	mapping map_status;
	string *mname;
	int i, j;
	mixed perform_actions = ({});
	mixed combat_actions = ({});
	mixed msg = ({});

	if (this_object()->query("owner") == me->query("id"))
	{
		message_vision(HIY "$N眼中突然闪过惊惧的目光，双眼冒火般瞪着$n，大声喊道：" + RANK_D->query_self_rude(ob) + "就是" + ob->query("fname") + "！" + RANK_D->query_rude(me) + "！纳命来吧！\n" NOR, ob, me);
		me->start_busy(1);
		ob->fight_ob(me);
		//		me->fight_ob(ob);
		if (ob->query_temp("asked"))
			return 1;
		if (me->query("combat_exp") > 10000000)
			ob->add_temp("apply/dodge", 250);
		else if (me->query("combat_exp") > 5000000)
			ob->add_temp("apply/dodge", 200);
		else if (me->query("combat_exp") > 3000000)
			ob->add_temp("apply/dodge", 150);
		else if (me->query("combat_exp") > 1000000)
			ob->add_temp("apply/dodge", 100);
		else
			ob->add_temp("apply/dodge", 50);
		ob->set("title", ob->query("family_name") + "奸细");
		ob->set("name", ob->query("fname"));
		if (mapp(map_status = ob->query_skill_map()))
		{
			mname = keys(map_status);

			for (i = 0; i < sizeof(map_status); i++)
			{
				perform_actions = get_dir(SKILL_D(map_status[mname[i]]) + "/");
				for (j = 0; j < sizeof(perform_actions); j++)
				{
					sscanf(perform_actions[j], "%s.c", perform_actions[j]);
					if (mname[i] == "force")
						msg = ({(
								: exert_function, perform_actions[j]
								:)});
					else
						msg = ({(
								: perform_action, mname[i] + "." + perform_actions[j]
								:)});
					combat_actions += msg;
				}
			}
		}
		set("chat_chance_combat", 60);
		set("chat_msg_combat", combat_actions);
		ob->set_temp("asked", 1);
	}
	else
		message_vision(HIY "$N眼中寒光一闪，马上又变得漠然了，只是奇怪地看着$n。\n" NOR, ob, me);
	return 1;
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
	if (find_object(dest)->query("no_fight"))
		return 0;
	if (this_object()->is_fighting())
		return 0;
	command("go " + dir);
	return 1;
}

void init()
{
	add_action("do_halt", "halt");
	add_action("do_halt", "go");
	add_action("do_halt", "surrender");
}
int accept_hit(object me)
{
	notify_fail(HIW "不是你要抓的人，凑什么热闹！\n" NOR);
	if (this_object()->query("owner") == me->query("id") && this_object()->query_temp("asked"))
	{
		me->kill_ob(this_object());
		return 1;
	}
	return 0;
}
int accept_fight(object who) { return accept_hit(who); }
int accept_kill(object who) { return accept_hit(who); }
int accept_ansuan(object who) { return accept_hit(who); }
int accept_touxi(object who) { return accept_hit(who); }

int do_halt()
{
	object me = this_player();
	object ob = this_object();

	if (me->is_fighting(ob))
	{
		tell_object(me, HIR "奸细未除，怎能临阵退缩？\n" NOR);
		return 1;
	}
	return 0;
}

void dest_me(object ob)
{
	message_vision("只见$N忽然急转身行，纵身钻进行人中，转眼就踪迹皆无。\n", ob);
	destruct(ob);
}