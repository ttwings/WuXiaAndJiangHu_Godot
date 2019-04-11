// Last Modified by winder on Apr. 25 2001
//tianshaxing.c

#include <ansi.h>
inherit NPC;
void copyto(object ob);
void create()
{
	set_name("天杀星", ({"tian shaxing" ,"tian"}));
	set("gender", "男性");
	set("age", 40);
	set("long", "他是七杀门的首领。\n");
	set("per", 10);
	set("attitude", "peaceful");
    //  seteuid(getuid());

	set("str", 25);
	set("int", 35);
	set("con", 35);
	set("dex", 35);

	set("qi", 5000);
	set("max_qi", 5000);
	set("jing", 5000);
	set("max_jing", 5000);
	set("neili", 5000);
	set("max_neili", 5000);
	set("jiali", 150);

	set("combat_exp", 8000000);
	set("score", 0);
	set("shen_type", 0);

	set_skill("force", 250);
	set_skill("taiji-shengong", 300);
	set_skill("unarmed", 250);
	set_skill("taiji-quan", 300);
	set_skill("dodge", 250);
	set_skill("tiyunzong", 300);
	set_skill("sword", 250);
	set_skill("taiji-jian", 300);
	set_skill("parry", 250); 
	map_skill("force", "taiji-shengong");
	map_skill("unarmed", "taiji-quan");
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	create_family("七杀门", 1, "杀手");
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.sui" :),
	}));   
	setup();
	carry_object("/clone/weapon/gangjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	object ob;
  object shu=present("zhan shu",this_player());
  if (shu && shu->is_zhanshu())
    set("pk_target",this_player());

	if ( living(this_object())  &&
	   interactive(ob=this_player()) && 
     ob==query("pk_target") )
			{
				remove_call_out("killing");
				call_out("killing", 0, ob);
			}
	if (query("inited")) return;
	remove_call_out("dest");
	call_out("dest",600);
  set("inited",1);
}

void dest()
{
	object ob=this_object();
	if ( !living(ob) || ob->is_busy() || ob->is_fighting() )
	{
		remove_call_out("dest");
		call_out("dest",300);
		return;
	}
	message("channel/snow",HIC"【"HIM"侠客行一百"HIC"】"HIW"七杀门首领天杀星：看来中原的高手都是胆小鬼，我回去卷土重来！\n"NOR,users());
	message("channel/snow",HIC"【"HIM"侠客行一百"HIC"】"HIW"七杀门首领天杀星仰天“哈哈”长笑几声。\n"NOR,users());
	message_vision("$N一个纵身，转眼就消失在茫茫人海之中。\n",ob);
	destruct(ob);
}

void die()
{
	object me;
	object shu;
	me = query("pk_target");
	shu = present("zhan shu",me);
	message_vision("$N说道：“哎,看来我命该如此啊！”说完两眼一闭倒地死了。\n", this_object());
  if (userp(me) &&  environment(me)==environment(this_object()) &&
   objectp(shu) &&  shu->is_zhanshu())
	{
  destruct(shu);
	me->add("combat_exp",25000);
	me->add("potential",2500);
	tell_object(me,HIW"你杀死七杀门首领天杀星有功，奖励你 25K 经验和 2500 点潜能！\n"NOR);
	message("channel/snow",HIM"【谣言】某人：天杀星被"+me->name()+HIM"杀死了。\n"NOR,users());
  }
	::die();
}

void if_die()
{
	if ( !query("pk_target")->is_ghost() )
	{
		remove_call_out("if_die");
		call_out("if_die",3);
		return;
	}
	message("channel/snow",HIC"【"HIM"侠客行一百"HIC"】"HIW"七杀门首领天杀星大笑道：中原的武功也不过如此嘛！老子天下第一！待我回去卷土重来！哈！哈！哈！\n"NOR,users());
	message_vision("$N一个纵身，转眼就消失在茫茫人海之中。\n",this_object());
	destruct(this_object());
}

int accept_hit(object me)
{
	object who, ob;
  object shu=present("zhan shu",me);
	ob = this_object();
	who = query("pk_target");
//	if ( who==me ) return 1;
	if ( shu && shu->is_zhanshu()) 
	{
		if (me!=ob->query_temp("last_damage_from")) copyto(me);
		return 1;
	}
	message_vision(HIW "$N一见$n在此捣乱，跳出来大喝一声道：臭贼！给我滚到一边去，不要妨碍老子决斗！\n"NOR,ob,me);
	message_vision("只见$N飞起一个三百六十度旋风腿将$n踢了出去。\n",ob,me);
	me->move("/d/city/wumiao");
	message_vision("只听“乒”地一声，$N被人一脚踢了过来，模样狼狈万状。\n",me);
  me->unconcious();
  me->start_busy(5);
	return notify_fail("");
}
int accept_fight(object who)	{return accept_hit(who);}
int accept_kill(object who)		{return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)	{return accept_hit(who);}

void killing(object ob)
{
	if ( environment(this_object()) != environment(ob) ) return;
	if ( (environment(ob)->query("no_fight")) ) return;

	message_vision("$N对著$n喝道：「"+RANK_D->query_rude(ob)+"！今天不是你死就是我亡！」\n",this_object(),ob);

  copyto(ob);
  
	this_object()->kill_ob(ob);
	remove_call_out("if_die");
	call_out("if_die",3);
	return;
}
void copyto(object player)
{
	object me=this_object();
	float exper;
	int i,level;
	int neili;
	mapping skill_status;
	string *sname;
	
	if (me->query("combat_exp") < player->query("combat_exp"))
	    me->set("combat_exp",player->query("combat_exp"));
	exper = to_float(me->query("combat_exp"));
	level = ceil( pow( exper*10.0, 0.333333));
  skill_status = me->query_skills();
  sname  = keys(skill_status);
	for (i=0;i<sizeof(skill_status);i++)
	{
		me->set_skill(sname[i],level);
	}
	me->revive(1);
	me->set("qi",me->query("max_qi"));
	me->set("eff_qi",me->query("max_qi"));
	me->set("jing",me->query("max_jing"));
	me->set("eff_jing",me->query("max_jing"));
	neili = 5000;
	if (player->query("neili") > neili ) neili = player->query("neili");
	if (player->query("max_neili") > neili ) neili = player->query("max_neili");
  me->set("max_neili",neili);
  me->set("neili",neili);
  me->set("jiali", neili/20);
}