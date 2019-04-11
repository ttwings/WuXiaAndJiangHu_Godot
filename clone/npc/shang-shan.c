// shang-shan.c 赏善使者

#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif
#define SHIZHE NPCDATA + "shang-shan"

inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;

string query_save_file()
{
	return SHIZHE;
}

void create()
{
	object ob,player;
	seteuid(getuid());

	if (!restore()) {
	set_name("东方日", ({ "shangshan shizhe", "shangshan", "shizhe" }) );
	set("title", "赏善使者" );
	set("gender", "男性" );
	set("age", 35);
	set("no_get", "1");
      set("long","一位笑容可掬的中年人，他就是乐善好施，爱贫如子的武林赏善使者。\n");
	set("attitude", "heroism");
	set("generation",0);
	set("winner","none");

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
	set("jiali", 30);
	set("shen_type", 0);

	set("no_clean_up",1);
	set("combat_exp", 400000);

	set_skill("force",  90); 
	set_skill("unarmed",90);
	set_skill("sword",  90);
	set_skill("dodge",  90);
	set_skill("parry",  90);

	set("weapon", "/d/shaolin/obj/changjian");
	set("armor", "/d/city/obj/cloth");

	setup();

	carry_object("/d/shaolin/obj/changjian")->wield();
	carry_object("/d/city/obj/cloth")->wear();        
	}
	else {
		set("id", "shangshan shizhe");
		set_name(query("name"), ({ query("id") }));
		setup();
//	carry_object(this_object()->query("weapon"))->wield();
		if( this_object()->query("weapon") ) 
		{
			ob = new(query("weapon"));
			if (ob->query("player"))
			{
				if (objectp(player=NPC_D->create_player(query("winner"))))
				{
					ob->copyto(player);
					destruct(player);
				}
				else destruct(ob);
			}
		}
		if (objectp(ob)) {ob->move(this_object());ob->wield();}
		if( this_object()->query("armor") )
		{
			ob = new(query("armor"));
			if (ob->query("player"))
			{
				if (objectp(player=NPC_D->create_player(query("winner"))))
				{
					ob->copyto(player);
					destruct(player);
				}
				else destruct(ob);
			}
		}
		if (objectp(ob))	{ob->move(this_object());ob->wear();}
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

	command("say 你想谋害本使者，当真是自找死路！ 座下红衣武士何在！");
	message_vision("四周的红衣武士群起对$N发动攻击！\n", this_player());

	for(i=0; i<4; i++) {
		if( objectp( ob = present("wei shi " + (i+1), environment(this_object())) ) )
				 ob->kill_ob(this_player());	
		else	this_object()->kill_ob(this_player());		
	}

	return 1;
}

int accept_fight(object ob)
{
	object me, mengzhu, fae;
	string name1, name2;
 
	me  = this_object();
	seteuid(getuid());
	mengzhu = new("/clone/npc/meng-zhu");
	name1 = mengzhu->query("winner");
	destruct(mengzhu);

	if( this_player()->query("id") == name1 )
		return notify_fail("你已经是武林盟主，还要抢当赏善使者？！\n");

	fae = new("/clone/npc/fa-e");
	name2 = fae->query("winner");
	destruct(fae);
	
	if( this_player()->query("id") == name2 )
		return notify_fail("你已经是罚恶使者，还要抢当赏善使者？！\n");

	if ( me->query("winner") == ob->query("id") ) 
		return notify_fail("你跟你自己打什么架？！\n");

	if ( me->is_fighting() ) 
		return notify_fail("已经有人正在挑战赏善使者！\n");

	me->set("eff_qi", me->query("max_qi"));
	me->set("qi",     me->query("max_qi"));
	me->set("jing",   me->query("max_jing"));
	me->set("neili",  me->query("max_neili"));

	remove_call_out("checking");
	call_out("checking", 1, me, ob);
	
	return 1;
}

int checking(object me, object ob)
{

	object obj;
	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");

	if (me->is_fighting()) {
		if ( (me->query("qi")*100 / my_max_qi) <= 80 )
			command("exert recover");

		call_out("checking", 1, me, ob);
		return 1;
	}

	if ( !present(ob, environment()) ) return 1; 

	if (( (int)me->query("qi")*100 / my_max_qi) <= 50 ) {
		command("say 佩服佩服，看来我的担子可以交卸了，恭喜你成为武林赏善使者！\n");
		command("chat 恭喜" + ob->query("name") + "被推举为现任武林赏善使者！\n");
		remove_call_out("do_copy");
		call_out("do_copy", 0, me, ob);
		return 1;
	}

	if (( (int)ob->query("qi")*100 / his_max_qi) < 50 ) {
		command("say 看来" + RANK_D->query_respect(ob) + 
			"还得多加练习，方能在当今武林中有所作为 !\n");
		return 1;
	}

	return 1;  
}

int do_copy(object me, object ob)
{
	me->set("winner", ob->query("id"));
	me->add("generation", 1);	

	me->set("name",  ob->query("name") );
	me->set("title", "第" + chinese_number(me->query("generation")) + "代赏善使者");
	me->set("short", me->query("title") + " " + me->query("name") + "(" + capitalize(ob->query("id")) + ")");
	me->delete("title");

//	ob->delete_temp("apply/short");
//	ob->set_temp("apply/short", ({me->short()}));
	ob->set_temp("apply/short",({me->query("short")}));
	
	me->set("title", "第" + chinese_number(me->query("generation")) + "代赏善使者");
	me->set("short", me->query("title") + " " + me->query("name") + "(shangshan shizhe)");
	me->delete("title");

	remove_call_out("do_clone");
	call_out("do_clone", 0, me, ob);

	return 1;
}


int do_clone(object me, object ob)
{
	object *inv, newtmp;
	mapping hp_status, skill_status, map_status, prepare_status;
	string *sname, *mname, *pname;
	int i, temp;

	seteuid( geteuid(me) );

/* delete and copy skills */

	if ( mapp(skill_status = me->query_skills()) ) {
		skill_status = me->query_skills();
		sname  = keys(skill_status);

		temp = sizeof(skill_status);
		for(i=0; i<temp; i++) {
			me->delete_skill(sname[i]);
		}
	}

	if ( mapp(skill_status = ob->query_skills()) ) {
		skill_status = ob->query_skills();
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			me->set_skill(sname[i], skill_status[sname[i]]);
		}
	}
	
/* delete and copy skill maps */

	if ( mapp(map_status = me->query_skill_map()) ) {
		mname  = keys(map_status);

		temp = sizeof(map_status);
		for(i=0; i<temp; i++) {
			me->map_skill(mname[i]);
		}
	}

	if ( mapp(map_status = ob->query_skill_map()) ) {
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			me->map_skill(mname[i], map_status[mname[i]]);
		}
	}
	
/* delete and copy skill prepares */

	if ( mapp(prepare_status = me->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		temp = sizeof(prepare_status);
		for(i=0; i<temp; i++) {
			me->prepare_skill(pname[i]);
		}
	}

	if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
		pname  = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++) {
			me->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}

/* unwield and remove weapon & armor */

	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++) {
		destruct(inv[i]);
	}
	set("weapon", 0);
	set("armor", 0);

/* wield and wear weapon & armor */

	inv = all_inventory(ob);
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]->query("weapon_prop/damage") > 100 
		||  inv[i]->query("armor_prop/armor") > 100 ) continue;

		if( inv[i]->query("weapon_prop") &&  inv[i]->query("equipped") ) {
//			carry_object(base_name(inv[i]))->wield();
			me->set("weapon", base_name(inv[i]));
		}
		else if( inv[i]->query("armor_prop") &&  inv[i]->query("equipped") ) {
//			carry_object(base_name(inv[i]))->wear();
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

		me->set("max_qi",    hp_status["max_qi"]);
		me->set("eff_qi",    hp_status["eff_qi"]);
		me->set("qi",        hp_status["qi"]);
		me->set("max_jing",  hp_status["max_jing"]);
		me->set("eff_jing",  hp_status["eff_jing"]);
		me->set("jing",      hp_status["jing"]);
		me->set("max_neili", hp_status["max_neili"]);
		me->set("neili",     hp_status["neili"]);
		me->set("jiali",     hp_status["jiali"]);
		me->set("gender",    hp_status["gender"]);
		me->set("combat_exp",hp_status["combat_exp"]);

	save();

//	tell_object(ob, "状态储存完毕。\n");

	newtmp = new("/clone/npc/shang-shan");
	newtmp->move("/d/taishan/xiayi");
	destruct(me);

	return 1;
}

