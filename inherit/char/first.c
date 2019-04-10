// first.c 掌门弟子
// Last Modified by Winder on Mar. 27 2000
// Based on XYJ4.51
// Modified by Zeratul 4.11 2001 首次成为掌门弟子可获得赏善罚恶令，加大了挑战掌门弟子的难度。
// qingyun 2004

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

string zname(object);
void reset(object me);// 初始化武功、经验、title 等
void create_identity (mixed master, mixed where);//为弟子重置准备(只一次)
int init_identity (object me, object master, object where);//重置弟子restore
int save_record(object me, object ob);//完全拷贝ob的武功等给me 并保存
void self_adjust (object me); //设所有武功60 气血同reset  用于copy from master后恢复 
string zm_apply();// 处理ask about 掌门事件
int fully_recover (object me); // 开始打架之前 恢复状态
int check_result(object me, object ob); // 开始打架 并检查结束
void find_master (object me, object ob); // 带去掌门路上循环检测
void master_announce (object me, object who, object ob); //掌门通知
int convert_identity (object me, object ob);//更新掌门弟子

void create()
{
	set_name("掌门大弟子", ({ "zhang men", "zhangmen", "first" }) );
	set("gender", "男性" );
	set("age", 30);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("per", 30);
	set("no_get", 1);
	set("no_get_from", 1);
	set("long", "这是本门掌门大弟子。你如果不服，可以挑战。\n" );
	set("attitude", "heroism");
	set("combat_exp", 100000);
	set("current_player","none of us");
	setup();
	carry_object("clone/misc/cloth")->wear();
}

void init()
{
	object me = this_object();

	me->create_identity(me->query("master_dir"), me->query("start_room"));
	me->set("inquiry", ([
		"掌门大弟子" : (: zm_apply :),
		"掌门弟子" : (: zm_apply :),
		"大弟子" : (: zm_apply :),
		"掌门" : (: zm_apply :),
		"挑战" : (: zm_apply :),
	]) );
	add_action("do_bandage","bandage");
	add_action("do_reset", "reset");
}
int do_reset(string arg)
{
	object ob=this_player();
	object me=this_object();
	if (!wizardp(ob)) return 0;
	if (arg != "zhangmen") return notify_fail("你要reset zhangmen吗？\n");
	set_name("掌门大弟子", ({ "zhang men", "zhangmen", "first" }) );
	me->reset_me(me);
	me->set("current_player","none of us");
	me->delete("weapon");
	me->save();
  write("重置"+me->query("family/family_name")+"掌门弟子成功。\n");
  return 1;
}

void create_identity (mixed master, mixed where)
{
	object master_ob, where_ob;

	if (this_object()->query("created")) return;
	this_object()->set("created",1);

	if (objectp(master)) master_ob = master;
	else	master_ob = new (master);

	if (objectp(where)) where_ob = where;
	else
	{
		call_other(where,"???");
		where_ob = find_object(where);
	}
	init_identity (this_object(), master_ob, where_ob);
}

int init_identity (object me, object master, object where)
{
	mapping skill_status;
	string *skillnames;
	int i;

	reset_eval_cost();
//	me->setup();

	me->move(where,1);
	me->set("where",base_name(where));

	me->set("gender", master->query("gender") );
	me->set("current_master",master->query("id"));
	me->set("current_master_base_name",base_name(master));
	me->set("family/generation",master->query("family/generation")+1);
	me->set("family/family_name",master->query("family/family_name"));
	me->set("title",me->query("family/family_name")+zname(me));
	me->set("short",me->query("name")+"("+capitalize(me->query("id"))+")");

	me->restore();
	if (me->query("current_player")!="none of us") 
	{
		fully_recover(me);
		return 1;
	}

	remove_call_out("self_adjust");
	call_out("self_adjust", 1, me);

	me->reset_me(me);
	me->set("current_player","none_of_us");
	me->set("new_player",1);
	save_record(me, master);

	return 1;
}

int save_record(object me, object ob)
{
	object *inv;
	mapping hp_status, skill_status, map_status ,prepare_status;
	string *skillnames, *mapnames , *pname;
	int i, weapon_cnt, armor_cnt;
	object obj;

	reset_eval_cost();
	hp_status = ob->query_entire_dbase();
	me->set("str", hp_status["str"]);
	me->set("int", hp_status["int"]);
	me->set("con", hp_status["con"]);
	me->set("dex", hp_status["dex"]); 
	me->set("per", hp_status["per"]);
	me->set("age", hp_status["age"]);

	me->set("max_jing",   hp_status["max_jing"]);
	me->set("eff_jing",   hp_status["max_jing"]);
	me->set("jing",       hp_status["max_jing"]);
	me->set("max_qi",     hp_status["max_qi"]);
	me->set("eff_qi",     hp_status["max_qi"]);
	me->set("qi",         hp_status["max_qi"]);
	me->set("max_neili",  hp_status["max_neili"]);
	me->set("neili",      hp_status["max_neili"]*2);
	me->set("gender",     hp_status["gender"]);
	me->set("combat_exp", hp_status["combat_exp"]);

  if ( ob->query("weapon/make"))
  {
		me->set("weapon/type",    ob->query("weapon/type"));
		me->set("weapon/value",   ob->query("weapon/value"));
		me->set("weapon/name",    ob->query("weapon/name"));
		me->set("weapon/id",      ob->query("weapon/id"));
		me->set("weapon/lv",      ob->query("weapon/lv"));
		me->set("weapon/or",      ob->query("weapon/or"));
		me->set("weapon/time",    ob->query("weapon/time"));
		me->set("weapon/make",    ob->query("weapon/make"));
		me->set("weapon/killed",  ob->query("weapon/killed"));
	}

/// copy skill//
	skill_status = me->query_skills();
	if ( mapp(skill_status) )
	{
		skillnames  = keys(skill_status);
		for(i=0; i<sizeof(skillnames); i++) 
		{
			me->delete_skill(skillnames[i]);
		}
	}

	skill_status = ob->query_skills();
	if ( mapp(skill_status) )
	{
		skillnames  = keys(skill_status);
		for(i=0; i<sizeof(skillnames); i++) 
		{
			me->set_skill(skillnames[i],skill_status[skillnames[i]]);
		}
	}
/// copy skill end //
  
	me->set("jiali",me->query_skill("force")/2);
	reset_eval_cost();
	if (! me->query("new_player"))
	{
		me->save();
		reset_eval_cost();
		return 1;
	}
	me->set("new_player",0);

/// copy enable//
	map_status = me->query_skill_map();
	if ( mapp(map_status ) ) 
	{
		mapnames = keys(map_status);
		for(i=0; i<sizeof(mapnames); i++) 
		{
			me->map_skill(mapnames[i]);
		}
	}

	map_status = ob->query_skill_map();
	if ( mapp(map_status) ) 
	{
		mapnames  = keys(map_status);
		for(i=0; i<sizeof(mapnames); i++) 
		{
			me->map_skill(mapnames[i], map_status[mapnames[i]]);
		}
	}
/// copy enable end//
	
/// copy prepare//
	prepare_status = me->query_skill_prepare();
	if ( mapp(prepare_status) )
	{
		pname = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++)
		{
			me->prepare_skill(pname[i]);
		}
	}

	prepare_status = ob->query_skill_prepare();
	if ( mapp(prepare_status) )
	{
		pname = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++)
		{
			me->prepare_skill(pname[i], prepare_status[pname[i]]);
		}
	}
/// copy prepare end //
  
	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++) 
	{
		destruct(inv[i]);
	}

// save once here, an external bug might stop the following
//	me->setup();
	me->save();

	weapon_cnt = 0;
	armor_cnt = 0;
	inv = all_inventory(ob);
	for(i=0; i<sizeof(inv); i++) 
	{
		if ( !weapon_cnt && inv[i]->query("equipped") &&
		    !inv[i]->is_unique() && inv[i]->query("skill_type") )
		{
			seteuid(getuid(ob));
			obj = new(base_name(inv[i]));
			if (obj)
			{
				obj->set("value",0);
 				obj->set("no_get",1);
				if(obj->move(me)) obj->wield();
  			me->set("weapons", base_name(inv[i]));
	  		weapon_cnt = 1;
			}
		}
		else
		if ( !armor_cnt && inv[i]->query("equipped") &&
		    !inv[i]->is_unique() && !inv[i]->query("armor_type") ) 
		{
      seteuid(getuid(ob));
			obj = new(base_name(inv[i]));
			if (obj)
			{
				obj->set("value",0);
				obj->set("no_get",1);
				if(obj->move(me)) obj->wear();
  			me->set("armor", base_name(inv[i]));
	  		armor_cnt = 1;
			}
		}
		else 
		if( weapon_cnt && armor_cnt )		break;
	}

//	me->setup();
	seteuid(getuid());
	me->save();
	reset_eval_cost();
	return 1;
}

void self_adjust (object me)
{
	mapping skill_status;
	string *skillnames;
	int i;

	me->set("max_jing", 600);
	me->set("eff_jing", 600);
	me->set("jing", 600);
	me->set("max_qi", 600);
	me->set("eff_qi", 600);
	me->set("qi", 600);
	me->set("neili", 600);
	me->set("max_neili", 600);
	me->set("jiali", 60);
	me->set("combat_exp", 100);

	skill_status = me->query_skills();
	if ( mapp(skill_status) )
	{
		skillnames = keys(skill_status);
		for(i=0; i<sizeof(skillnames); i++)
			me->set_skill(skillnames[i], 60);
	}
	carry_object("/clone/misc/cloth")->wear();
	me->save();
}

string zm_apply()
{
	object me = this_object();
	object ob = this_player();

	if (me->query("family/family_name") != ob->query("family/family_name")) 
	{
		return "我便是"+me->query("family/family_name")+"掌门弟子！\n";
	}
	if (ob->query("betrayer") || ob->query("detach/"+me->query("family/family_name")) )
	{
		return "你曾叛师欺祖，言无信行不轨，岂能出任掌门弟子一职！\n";
	}
	if (me->query("current_player") == ob->query("id")) 
	{
		return "你又糊涂了！\n";
	}
	if (me->is_fighting())
	{
		return "我在比武之中，请稍候。\n";
	}
	ob->set_temp("zm_applied", 1);
	fully_recover (me);

	ob->fight_ob(me);
	me->fight_ob(ob);
	me->set_temp("zhangmen/kill",0);
	remove_call_out("check_result");
	call_out("check_result", 1, me, ob);
	return "好！你有意出任掌门弟子一职？我们就切磋一下吧！\n";
}

int fully_recover (object me)
{
	object *inv;
	object ob;
	string player_name;
	object current_player;
	int i,j;
	mapping map_status;
	string*	mname;
	mixed perform_actions = ({});
	mixed combat_actions = ({});
	mixed msg =({});
	mapping skl;
	string *skname;

	reset_eval_cost();
	me->set("eff_jing", me->query("max_jing"));
	me->set("jing",     me->query("max_jing"));
	me->set("eff_qi",   me->query("max_qi"));
	me->set("qi",       me->query("max_qi"));
	me->set("neili",    me->query("max_neili")*2);
	// Modified by Zeratul 4.11 2001
	me->set("jiali",    me->query_skill("force")/2);

	if ( mapp(map_status = me->query_skill_map()) ) 
	{
		mname  = keys(map_status);

		for(i=0; i<sizeof(map_status); i++) {
			perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
			for ( j = 0; j < sizeof( perform_actions ); j++ )
			{
				if (sscanf( perform_actions[j], "%s.c", perform_actions[j] ) == 1)
				if ( mname[i] == "force" )
					msg = ({ (: exert_function, perform_actions[j] :) });
				else
					msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
				combat_actions += msg;
			}
		}	
	}
	
	set( "chat_chance_combat", 80);		
	set( "chat_msg_combat", combat_actions );		


	player_name = me->query("current_player");
	if (! player_name || player_name == "none of us" 
	                  || player_name == "none_of_us" ) return 1;
	if (current_player = find_player(player_name))
	{
		if (current_player->query("combat_exp") > me->query("combat_exp"))
			save_record (me, current_player);
	}
	else if (current_player = LOGIN_D->find_body(player_name))
	{
		if (current_player->query("combat_exp") > me->query("combat_exp"))
			save_record (me, current_player);
	}
	else
	{
		if (objectp(current_player = NPC_D->create_player(player_name)))
		if (current_player->query("combat_exp") > me->query("combat_exp"))
			save_record (me, current_player);
		destruct (current_player);
	}

	inv = all_inventory(me);
  for (i=0;i<sizeof(inv);i++)
    destruct(inv[i]);

	if (me->query("weapons"))
	{
		seteuid(getuid());
		ob = new(me->query("weapons"));
		if (strsrch(me->query("weapons"), "m_weapon") >= 0)
		{
		   ob->copyto(me);
		}
		ob->set("value",0);
		ob->set("no_get",1);
		if(ob->move(me)) ob->wield();  
	}

	if (me->query("armor"))
	{
		seteuid(getuid());
		ob = new(me->query("armor"));
		ob->set("value",0);
		ob->set("no_get",1);
		if(ob->move(me)) ob->wear(); 
	}
  seteuid(getuid());
	reset_eval_cost();
	skl = me->query_skills();
	skname = keys(skl);
	for (i=0;i<sizeof(skl);i++)
	{
		if (skl[skname[i]] > 200)
			me->set_skill(skname[i],200);
	}
	if (me->query("combat_exp")>2000000)
		me->set("combat_exp",2000000);
	if (me->query("max_neili")>3000)
	{
		me->set("max_neili",3000);
		me->set("neili",6000);
		me->set("jiali",150);
	}
	return 1;
}

int check_result(object me, object ob)
{
	int my_max_qi, his_max_qi;

	my_max_qi  = me->query("max_qi");
	his_max_qi = ob->query("max_qi");
	if (me->is_fighting())
	{
		remove_call_out("check_result");
		call_out("check_result",1, me, ob);
		return 1;
	}
	if ( !living(me) || me->query_temp("noliving") ||
		(int)me->query("qi") < 1 ||(int)me->query("jing") < 1 )
		return 1;
	if (((int)me->query("qi")*100/(1+my_max_qi)) <= 50 )
	{
		object who;
		message_vision ("$N翻身下拜，连声佩服！\n",me);
		if (me->query_temp("zhangmen/kill") && ob->query_temp("zm_applied"))
		{
			message_vision ("$N皱了皱眉道：此次比武我未能静心尽力，希望重新来过。\n", me);
			return 1;
		}
		if( ob->query_temp("zm_applied") != 1 ) return 1;
		if (me->query("current_master"))
			who=present(me->query("current_master"),environment(me));
	  if (who && who->query("id")!=me->query("current_master")) who = 0; 
		if (who)
		{ 
			call_out("master_announce",1,me,who,ob);
		}
		else
		{
			message_vision("$N躬身对$n道：恭请拜见师父。\n",me,ob);
			command ("follow "+ob->query("id"));
			if (! me->query("where"))
				me->set("where",base_name(environment(me)));
			remove_call_out("find_master");
			call_out("find_master", 1, me, ob);
		}
		return 1;
	}
	else if (( (int)ob->query("qi")*100/his_max_qi)<=50)
	{
		message_vision ("$N将$n扶起。\n",me,ob);
	}
	else 
	{
		message_vision ("$N皱了皱眉道：此次比武未能一较高下，希望重新来过。\n", me);
	}
	return 1;  
}

void find_master (object me, object ob)
{
	object who = present(me->query("current_master"),environment(me));

	if (who && who->query("id")!=me->query("current_master")) who = 0; 
	if (! who)
	{
		remove_call_out("find_master");
		call_out("find_master", 1, me, ob);
	}
	else
	{
		message_vision ("$N见了师父赶紧下拜，又抬起头朝$n使了个眼色。\n\n",me,ob);
		message_vision ("$N微微地点了点头。\n\n",who);
		message_vision ("$N退下。\n\n",me);
		me->set_leader(0);
		call_out("master_announce",1,me,who,ob);
		me->move(me->query("where"));
	}
}

void master_announce (object me, object who, object ob)
{
	// Modified by Zeratul 4.11 2001
	object ling;

	CHANNEL_D->do_channel(who,"chat","本派掌门弟子"+ob->query("name")+"今日走马上任。恭请各位大侠多加捧场！");
	ob->delete_temp("zm_applied");
	me->set("new_player",1);

	convert_identity(me, ob);
	// Modified by Zeratul 4.11 2001
	if ( !ob->query("xkd/ling") )
	{
		seteuid(getuid());
		ling = new( "/d/xiakedao/obj/tongpai1" );
		ling->set( "own", ob->query("id") );
		ling->move( ob );
		ling = new( "/d/xiakedao/obj/tongpai2" );
		ling->set( "own", ob->query("id") );
		ling->move( ob );
		message_vision( HIY"$N对$n说道：侠客岛昨日送来赏善罚恶令，邀请为师上岛。\n                你是本门掌门弟子，就代为师走一趟吧。\n"NOR, who, ob );
		message_vision( HIC"说完，$N把两块令牌交到$n手里。\n"NOR, who, ob );
		ob->set( "xkd/ling", 1 );
		ob->set( "xkd/time", time() + 86400 );
	}
}


int convert_identity (object me, object ob)
{
	object who;
	int flag;
	string err;

	reset_eval_cost();
	who = find_player(me->query("current_player"));
	if (!who) 
	{ 
		flag = 1;
		who = NPC_D->create_player(me->query("current_player"));
	}
	if (objectp(who))
	{
		if (who->query("zhangmen/title_old"))
			who->set("title",who->query("zhangmen/title_old"));
		else if (who->query("family/family_name"))
		{
			who->set("title",
			sprintf("%s第%s代%s",
			who->query("family/family_name"),
			chinese_number(who->query("family/generation")),
			who->query("family/title")));
			who->save();
		}
		if (flag == 1) 
		{
			who->save();
			destruct(who);
		}
	}
	ob->set("zhangmen/base_name",base_name(me));
	ob->set("zhangmen/data_name",me->query_save_file());
	ob->set("zhangmen/title_old",ob->query("title"));
	ob->set("zhangmen/title",ob->query("family/family_name")+zname(ob));
	ob->set("title",ob->query("family/family_name")+zname(ob));
//	ob->save();

	me->reset_me(me);
	me->set("name", ob->query("name") );
	me->set("gender", ob->query("gender") );
	me->set("current_player",ob->query("id"));
	me->set("title",ob->query("family/family_name")+zname(ob));
	me->set("short",me->query("name")+"("+capitalize(me->query("id"))+")");
	save_record(me,ob);
	return 1;
}

void die()
{
        message_vision(HIW"$N大喝到：“今日算你走运，待我请来本门师尊为我报仇！”说话间人已负伤遁去！\n"NOR,this_object());	
	destruct(this_object());
}

string query_save_file()
{
	string str = query("save_file");
	int i;

	if (str) return str;
	str = DATA_DIR+"zhangmen/"+query("current_master");
//	for (i = 0; i < sizeof(str); i++) if (str[i]==' ') str[i] = '_';
  str = replace_string(str," ","_");
	return str;
}

void set_save_file(string str)
{
	set("save_file",str);
}

void kill_ob(object ob)
{
	object me = this_object();
	object master;

	if (me->query("current_master"))
		master = present(me->query("current_master"),environment(me));
	if (master) master->kill_ob(ob);
	me->set_temp("zhangmen/kill",1);
	::kill_ob(ob);
}

string zname(object ob)
{
	if( (string)ob->query("gender") == "女性" ) return "掌门大师姐";
	else return "掌门大师兄";
}

int do_bandage(string arg)
{
	object who = this_player();
	object me = present("zhang men",environment(who));

	if (! arg || me != present(arg, environment(me))) return 0;

	message_vision ("$N别有用心地要给$n包扎伤口。\n",who,me);
	call_out("no_bandage",1,who,me);
	return 1;
}

void no_bandage(object who, object me)
{
	message_vision ("$N向$n摇了摇头。\n",me,who);
}
int accept_hit(object me)
{
   command("say 我是堂堂掌门弟子！要切磋你找别人去。\n");
   return notify_fail("");
}
int accept_fight(object who)	{return accept_hit(who);}
int accept_kill(object who)		{return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)	{return accept_hit(who);}

void reset_me (object me)
{
	int i;
	object *inv;
	mapping skill_status, map_status ,prepare_status;
	string *skillnames, *mapnames , *pname;

	reset_eval_cost();
	if ( mapp(map_status = me->query_skill_map()) )
	{
		mapnames = keys(map_status);
		for(i=0; i<sizeof(mapnames); i++)
		{
			me->map_skill(mapnames[i]);
		}
	}

	if ( mapp(skill_status = me->query_skills()) )
	{
		skillnames = keys(skill_status);
		for(i=0; i<sizeof(skillnames); i++)
		{
			me->delete_skill(skillnames[i]);
		}
	}
	
	if ( mapp(prepare_status = me->query_skill_prepare()) )
	{
		pname = keys(prepare_status);

		for(i=0; i<sizeof(prepare_status); i++)
		{
			me->prepare_skill(pname[i]);
		}
	}
 
	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++)
	{
		destruct (inv[i]);
	}
  me->set_default_object(__FILE__);
	me->set("title",me->query("family/family_name")+zname(me));
	me->set("short",me->query("name")+"("+capitalize(me->query("id"))+")");

	me->set("weapons", 0);
	me->set("armor", 0);

	me->set_skill("force",  60); 
	me->set_skill("unarmed",60);
	me->set_skill("sword",  60);
	me->set_skill("dodge",  60);
	me->set_skill("parry",  60);

	me->set("max_jing", 600);
	me->set("eff_jing", 600);
	me->set("jing", 600);
	me->set("max_qi", 600);
	me->set("eff_qi", 600);
	me->set("qi", 600);
	me->set("neili", 600);
	me->set("max_neili", 600);
	me->set("jiali", 30);
	
	reset_eval_cost();
}