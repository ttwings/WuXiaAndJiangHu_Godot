/*  <SecCrypt CPL V3R05>  */
 
//  created  7/6/1997  by  snowcat
#include  <ansi.h>

inherit  NPC;

object  room  =  0;

void  create()
{
    set_name("青鬏龟童",  ({"gui  tong",  "tong"  }));
    set("gender",  "男性");
    set("age",  13);
    set("per",  30);
    set("long",  "一位扎着青鬏的龟童。\n");
    set("combat_exp",  5000);
    set_skill("force",  50);
    set_skill("unarmed",  50);
    set_skill("dodge",  50);
    set_skill("parry",  50);
    set("jing",  500);
    set("max_jing",  500);
    set("qi",  500);
    set("max_qi",  500);
    set("neili",  150);
    set("max_neili",  150);
    set("force_factor",  10);
    setup();
    carry_object(__DIR__"obj/linen")->wear();
}

void  init()
{
    ::init();
    add_action("do_fight",  "fight");
    add_action("do_kill",  "kill");
    if  (room  ==  0)
        room  =  environment  (this_object());
}

void  refuse_message  (object  me,  object  who)
{
    message_vision  ("$N说：别别，杀$N哪有赛龟有趣。\n",me,who);
}

int  do_fight(string  arg)
{
    object  who  =  this_player();
    object  me  =  this_object();

    if  (arg  &&  present(arg,environment(who))==me)
    {
        message_vision  ("$N看样子输红了眼，想找$n打架。\n",who,me);
        refuse_message  (me,who);
        return  1;
    }
    return  0;
}

int  do_kill(string  arg)
{
    object  who  =  this_player();
    object  me  =  this_object();

    if  (arg  &&  present(arg,environment(who))==me)
    {
        message_vision  ("$N看样子输红了眼，想杀$n。\n",who,me);
        refuse_message  (me,who);
        return  1;
    }
    return  0;
}
