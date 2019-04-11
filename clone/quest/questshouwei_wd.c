// /clone/quest/questshouwei_wd.c
// Modified by Sir 03/04/2003
#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;
inherit F_UNIQUE;
void create()
{
	set_name("蒙面人", ({ "mengmian  ren" }));
	set("age",30+random(10));
	set("long", 
"此人一身黑衣，手握利刃，一身修为甚是了得。\n");
	set("no_steal", 1);
	set("quest_no_guard",1);
	set( "chat_chance_combat", 80);         
        set( "chat_msg_combat",({
        		(: exert_function, "recover" :),
        		(: exert_function, "powerup" :),
           }) );
	setup();
	carry_object("/d/city/npc/obj/tiejia")->wear();
	carry_object("/clone/food/jiudai");
}

void init()
{
//	 add_action("do_halt","jiasi");
	 add_action("do_halt","surrender");
}

int accept_hit(object me)
{
	notify_fail(HIW"不是你要抓的人，凑什么热闹！\n"NOR);
	if( this_object()->query("owner") == me->query("id")) 
		return 1;
}
int accept_fight(object who)	{return accept_hit(who);}
int accept_kill(object who)		{return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)	{return accept_hit(who);}


int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if ( me->is_fighting(ob))
        {
                message_vision(HIW"$N喝道：“你既然识破我的身份，就休想活着离开！”\n"NOR, ob, me);
                return 1;
        }
        return 0;
}
