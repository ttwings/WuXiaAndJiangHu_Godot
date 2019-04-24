// /clone/npc/meng-zhu.c 武林盟主
// colored the title of 武林盟主(player) ,   ReyGod, 1/15/1997
// Modified by Zeratul Jan 11 2001 第一次当武林盟主将有资格上侠客岛。盟主会随机perform了。

#include <ansi.h>

#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif
#define MENGZHU NPCDATA + "meng-zhu"

inherit NPC;
inherit F_MASTER;
//inherit F_CLEAN_UP;
inherit F_UNIQUE;
inherit F_SAVE;
string query_save_file()
{
	return MENGZHU;
}
string ask_me();

void create()
{
	mapping map_status;
	string *mname;
	int i, j;
	object ob, player;
	mixed perform_actions = ({});
	mixed combat_actions = ({});
	mixed msg = ({});

	seteuid(getuid());

	if (!restore())
	{
		set_name("东方日", ({"shangshan shizhe", "shangshan", "shizhe"}));
		set_name("魏无双", ({"wulin mengzhu", "mengzhu", "zhu"}));
		set("title", "武林盟主");
		set("gender", "男性");
		set("age", 40);
		set("no_get", "1");
		set("long", "他就是雄踞武林，号召天下，威风赫赫的当今武林盟主。\n");
		set("attitude", "heroism");
		set("generation", 0);
		set("winner", "none");

		set("str", 25);
		set("con", 25);
		set("int", 25);
		set("dex", 25);

		set("max_qi", 500);
		set("eff_qi", 500);
		set("qi", 500);
		set("max_jing", 300);
		set("jing", 300);
		set("neili", 500);
		set("max_neili", 500);
		set("jiali", 40);
		set("shen_type", 0);

		set("no_clean_up", 1);
		set("combat_exp", 500000);

		set_skill("force", 100);
		set_skill("unarmed", 100);
		set_skill("sword", 100);
		set_skill("dodge", 100);
		set_skill("parry", 100);

		set("inquiry", ([
						   "大宗师":(
										: ask_me:),
		]));
		set("weapon", "/d/shaolin/obj/changjian");
		set("armor", "/d/city/obj/cloth");

		setup();

		carry_object("/d/shaolin/obj/changjian")->wield();
		carry_object("/d/city/obj/cloth")->wear();
	}
	else
	{
		set("id", "meng zhu");
		set_name(query("name"), ({query("id")}));
		set("inquiry", ([
						   "大宗师":(
										: ask_me:),
		]));

		if (mapp(map_status = this_object()->query_skill_map()))
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
		set("chat_chance_combat", 80);
		set("chat_msg_combat", combat_actions);
		setup();
		if (this_object()->query("weapon"))
		{
			ob = new (query("weapon"));
			if (ob->query("player"))
			{
				if (objectp(player = NPC_D->create_player(query("winner"))))
				{
					ob->copyto(player);
					destruct(player);
				}
				else
					destruct(ob);
			}
		}
		if (objectp(ob))
		{
			ob->move(this_object());
			ob->wield();
		}
		if (this_object()->query("armor"))
		{
			ob = new (query("armor"));
			if (ob->query("player"))
			{
				if (objectp(player = NPC_D->create_player(query("winner"))))
				{
					ob->copyto(player);
					destruct(player);
				}
				else
					destruct(ob);
			}
		}
		if (objectp(ob))
		{
			ob->move(this_object());
			ob->wear();
		}
	}
}

void init()
{
	add_action("do_kill", "kill");
}

int do_kill()
{
	object ob;
	int i;

	if (!present(this_player(), environment(this_object())))
		return 0;

	command("say 你想谋害本盟主，当真是吃了熊心豹子胆了！！");
	command("say 座下白衣武士何在！");

	message_vision("四周的白衣武士群起对$N发动攻击！\n", this_player());

	for (i = 0; i < 4; i++)
	{
		if (objectp(ob = present("wei shi " + (i + 1), environment(this_object()))))
			ob->kill_ob(this_player());
		else
			this_object()->kill_ob(this_player());
	}

	return 1;
}

int accept_fight(object ob)
{
	object me = this_object();

	if (ob->query("score") < 30000)
		//	 return notify_fail("哼，想挑战武林盟主，回去再历练几年吧！\n");
		return notify_fail("等你的江湖阅历凑够了三万，再来找我吧。\n");
	if (me->query("winner") == ob->query("id"))
	{
		return notify_fail("你跟你自己打什么架？！\n");
	}

	//	if (wizardp(this_player()))
	//		return notify_fail("巫师不能抢盟主之位！\n");

	if (me->is_fighting())
		return notify_fail("已经有人正在挑战武林盟主！\n");

	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("max_qi"));
	me->set("jing", me->query("max_jing"));
	me->set("neili", me->query("max_neili"));

	remove_call_out("checking");
	call_out("checking", 1, me, ob);

	return 1;
}

int checking(object me, object ob)
{

	object obj, ling;
	int my_max_qi, his_max_qi;

	my_max_qi = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting())
	{
		if ((me->query("qi") * 100 / my_max_qi) <= 80)
			command("exert recover");

		call_out("checking", 1, me, ob);
		return 1;
	}

	if (!present(ob, environment()))
		return 1;

	if (((int)me->query("qi") * 100 / my_max_qi) <= 50)
	{
		command("say 果然厉害，恭喜你成为当今武林盟主！\n");
		command("chat 哈哈哈，到底是长江後浪推前浪，一代新人换旧人！\n");
		command("chat 恭喜" + ob->query("name") + "被推举为当今武林盟主！\n");
		if (!ob->query("xkd/ling"))
		{
			ling = new ("/d/xiakedao/obj/tongpai1");
			ling->set("own", ob->query("id"));
			ling->move(ob);
			ling = new ("/d/xiakedao/obj/tongpai2");
			ling->set("own", ob->query("id"));
			ling->move(ob);
			tell_object(ob, HIY "你只觉得眼前一花，手中已多了两件物事。\n" NOR);
			ob->set("xkd/ling", 1);
			ob->set("xkd/time", time() + 86400);
		}
		remove_call_out("do_copy");
		call_out("do_copy", 1, me, ob);
		return 1;
	}

	if (((int)ob->query("qi") * 100 / his_max_qi) < 50)
	{
		command("say 看来" + RANK_D->query_respect(ob) +
				"还得多加练习，方能在当今武林中出人头地 !\n");
		return 1;
	}

	return 1;
}

int do_copy(object me, object ob)
{
	object ob1, ob2;
	string mengzhu, shangshan, fae;

	seteuid(getuid());

	me->set("winner", ob->query("id"));
	me->add("generation", 1);

	me->set("name", ob->query("name"));

	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", HIR + me->query("title") + NOR + " " + me->query("name") + "(" + capitalize(ob->query("id")) + ")");
	me->delete ("title");

	ob->delete_temp("apply/short");
	ob->set_temp("apply/short", ({me->short()}));
	// --record which mengzhu generataion this player got-------by ReyGod
	// = better to place this checking when players login.
	//	ob->set("mengzhu_gen",me->query("generation"));

	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", me->query("title") + " " + me->query("name") + "(Wulin mengzhu)");
	me->delete ("title");

	if (!(ob1 = find_living("shangshan")))
		ob1 = load_object("/clone/npc/shang-shan");
	shangshan = ob1->query("winner");

	if (!(ob2 = find_living("fae")))
		ob2 = load_object("/clone/npc/fa-e");
	fae = ob2->query("winner");

	if (ob->query("id") == shangshan)
	{
		rm(ob1->query_save_file() + __SAVE_EXTENSION__);
		destruct(ob1);
	}
	if (ob->query("id") == fae)
	{
		rm(ob2->query_save_file() + __SAVE_EXTENSION__);
		destruct(ob2);
	}

	remove_call_out("do_clone");
	call_out("do_clone", 0, me, ob);

	return 1;
}

int do_recopy(object me, object ob)
{
	me = this_object();
	ob = this_player();

	if (!present(this_player(), environment(this_object())))
		return 0;

	if (me->query("winner") != ob->query("id"))
		return notify_fail("你不是现任武林盟主！\n");
	;

	me->set("name", ob->query("name"));
	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", HIR + me->query("title") + NOR + " " + me->query("name") + "(" + capitalize(ob->query("id")) + ")");
	me->delete ("title");

	ob->delete_temp("apply/short");
	ob->set_temp("apply/short", ({me->short()}));
	// --record which mengzhu generataion this player got-------by ReyGod
	// = better to place this checking when players login.
	//	ob->set("mengzhu_gen",me->query("generation"));

	me->set("title", "第" + chinese_number(me->query("generation")) + "代武林盟主");
	me->set("short", me->query("title") + " " + me->query("name") + "(Wulin mengzhu)");
	me->delete ("title");

	remove_call_out("do_clone");
	call_out("do_clone", 0, me, ob);

	return 1;
}

int do_clone(object me, object ob)
{
	object *inv, newobj;
	mapping hp_status, skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i, j, temp;
	//	mixed* perform_actions;
	//	string action_name;
	// 	mixed combat_actions = ({});

	seteuid(geteuid(me));

	/* delete and copy skills */

	if (mapp(skill_status = me->query_skills()))
	{
		skill_status = me->query_skills();
		sname = keys(skill_status);

		temp = sizeof(skill_status);
		for (i = 0; i < temp; i++)
		{
			me->delete_skill(sname[i]);
		}
	}

	if (mapp(skill_status = ob->query_skills()))
	{
		skill_status = ob->query_skills();
		sname = keys(skill_status);

		for (i = 0; i < sizeof(skill_status); i++)
		{
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}

	/* delete and copy skill maps */

	if (mapp(map_status = me->query_skill_map()))
	{
		mname = keys(map_status);

		temp = sizeof(map_status);
		for (i = 0; i < temp; i++)
		{
			me->map_skill(mname[i]);
		}
	}

	if (mapp(map_status = ob->query_skill_map()))
	{
		mname = keys(map_status);

		for (i = 0; i < sizeof(map_status); i++)
		{
			me->map_skill(mname[i], map_status[mname[i]]);
		}
	}

	/* delete and copy skill prepares */

	if (mapp(prepare_status = me->query_skill_prepare()))
	{
		pname = keys(prepare_status);

		temp = sizeof(prepare_status);
		for (i = 0; i < temp; i++)
		{
			me->prepare_skill(pname[i]);
		}
	}

	if (mapp(prepare_status = ob->query_skill_prepare()))
	{
		pname = keys(prepare_status);

		for (i = 0; i < sizeof(prepare_status); i++)
		{
			me->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}

	/* unwield and remove weapon & armor */

	inv = all_inventory(me);
	for (i = 0; i < sizeof(inv); i++)
	{
		destruct(inv[i]);
	}
	set("weapon", 0);
	set("armor", 0);

	/* wield and wear weapon & armor */

	inv = all_inventory(ob);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (inv[i]->query("weapon_prop/damage") > 100 || inv[i]->query("armor_prop/armor") > 100)
			continue;

		if (inv[i]->query("weapon_prop") && inv[i]->query("equipped"))
		{
			carry_object(base_name(inv[i]))->wield();
			me->set("weapon", base_name(inv[i]));
		}
		else if (inv[i]->query("armor_prop") && inv[i]->query("equipped"))
		{
			carry_object(base_name(inv[i]))->wear();
			me->set("armor", base_name(inv[i]));
		}
	}

	/* copy entire dbase values */

	hp_status = ob->query_entire_dbase();

	me->set("str", hp_status["str"]);
	me->set("int", hp_status["int"]);
	me->set("con", hp_status["con"]);
	me->set("dex", hp_status["dex"]);
	me->set("age", hp_status["age"]);

	me->set("max_qi", hp_status["max_qi"]);
	me->set("eff_qi", hp_status["eff_qi"]);
	me->set("qi", hp_status["qi"]);
	me->set("max_jing", hp_status["max_jing"]);
	me->set("eff_jing", hp_status["eff_jing"]);
	me->set("jing", hp_status["jing"]);
	me->set("max_neili", hp_status["max_neili"]);
	me->set("neili", hp_status["neili"]);
	me->set("jiali", hp_status["jiali"]);
	me->set("gender", hp_status["gender"]);
	me->set("combat_exp", hp_status["combat_exp"]);
	save();

	tell_object(ob, "状态储存完毕。\n");

	newobj = new ("/clone/npc/meng-zhu");
	newobj->move("/d/taishan/fengchan");
	destruct(me);

	return 1;
}

int do_recover()
{
	object me, ob;
	mapping skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i;

	if (!present(this_player(), environment(this_object())))
		return 0;

	me = this_object();
	ob = this_player();

	if (me->query("winner") != ob->query("id"))
		return notify_fail("你不是现任武林盟主！\n");
	;

	/* delete and copy skills */

	if (mapp(skill_status = ob->query_skills()))
	{
		sname = keys(skill_status);

		for (i = 0; i < sizeof(skill_status); i++)
		{
			ob->delete_skill(sname[i]);
		}
	}

	if (mapp(skill_status = me->query_skills()))
	{
		sname = keys(skill_status);

		for (i = 0; i < sizeof(skill_status); i++)
		{
			ob->set_skill(sname[i], skill_status[sname[i]]);
		}
	}

	/* delete and copy skill maps */

	if (mapp(map_status = ob->query_skill_map()))
	{
		mname = keys(map_status);

		for (i = 0; i < sizeof(map_status); i++)
		{
			ob->map_skill(mname[i]);
		}
	}

	if (mapp(map_status = me->query_skill_map()))
	{
		mname = keys(map_status);

		for (i = 0; i < sizeof(map_status); i++)
		{
			ob->map_skill(mname[i], map_status[mname[i]]);
		}
	}

	/* delete and copy skill prepares */

	if (mapp(prepare_status = ob->query_skill_prepare()))
	{
		pname = keys(prepare_status);

		for (i = 0; i < sizeof(prepare_status); i++)
		{
			ob->prepare_skill(pname[i]);
		}
	}

	if (mapp(prepare_status = me->query_skill_prepare()))
	{
		pname = keys(prepare_status);

		for (i = 0; i < sizeof(prepare_status); i++)
		{
			ob->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}

	/* copy combat exp values */

	ob->set("combat_exp", me->query("combat_exp"));

	write("状态复元完毕。\n");

	return 1;
}

string ask_me()
{
	object *ob, room, me = this_player(), obj = this_object();
	int i, new_killer;

	if (!(room = find_object("/d/taishan/duzunju")))
		room = load_object("/d/taishan/duzunju");

	ob = all_inventory(room);
	for (i = 0; i < sizeof(ob); i++)
		if (userp(ob[i]))
		{
			return "“大宗师那里已经有客人了，一会再来吧。”\n";
		}
	ob = all_inventory(me);
	for (i = 0; i < sizeof(ob); i++)
		if (userp(ob[i]))
		{
			return "“你身上背了个谁？这样是不能去见大宗师的。”\n";
		}
	if (me->query("score") < 30000)
		return ("哼，就这点江湖阅历，大宗师是不会见你的！\n");
	me->move("/d/taishan/duzunju");
	tell_object(me, HIC "\n" + obj->query("name") + "告诉你说：好吧，我就送你过去。" + obj->query("name") + "回手拉开身后的小门，把你一把推了进去。\n" NOR);
	return "好吧，我就送你过去。" + obj->query("name") + "回手拉开身后的小门，把" + me->query("name") + "一把推了进去。\n";
}