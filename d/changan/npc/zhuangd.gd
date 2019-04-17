# /*  <SecCrypt CPL V3R05>  */
 
#  created  7/6/1997  by  snowcat
#include  <ansi.h>

# inherit  NPC;
extends Npc

var room  =  0;

func create():
    set_name("庄东","zhuang  dong");
    set("gender",  "男性");
    set("age",  30);
    set("per",  30);
    set("long",  "一位胖呵呵的庄东。\n");
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
    setup();
    carry_object(__DIR__"obj/magua")->wear();


func init():
    .init();
    add_action("do_fight",  "fight");
    add_action("do_kill",  "kill");
    add_action("do_steal",  "steal");
    add_action("do_cast",  "cast");
    add_action("do_exert",  "exert");
    if(room  ==  0):
        room = environment(this_object());


func refuse_message(me,who):
    message_vision  ("$N向$n乐呵呵地一笑了事。\n",me,who);


func do_fight(arg):
    var who  =  this_player();
    var me  =  this_object();

    if(arg  &&  present(arg,environment(who))==me):
        message_vision  ("$N看样子输红了眼，想找$n打架。\n",who,me);
        refuse_message  (me,who);
        return  1;
    return  0;


func do_kill(arg):
    var who  =  this_player();
    var me  =  this_object();

    if(arg  &&  present(arg,environment(who))==me) :
        message_vision  ("$N看样子输红了眼，想杀$n。\n",who,me);
        refuse_message  (me,who);
        return  1;
    return  0;

func do_cast(arg):
    var who  =  this_player();
    var me  =  this_object();

    message_vision  ("$N看样子输红了眼，想念咒语。\n",who,me);
    refuse_message  (me,who);
    return  1;
}

func do_exert(arg):
    var who  =  this_player();
    var me  =  this_object();

    message_vision  ("$N看样子输红了眼，想施内功。\n",who,me);
    refuse_message  (me,who);
    return  1;
}

func do_steal(arg):
    var who  =  this_player();
    var me  =  this_object();

    message_vision  ("$N看样子输红了眼，鬼鬼祟祟地想偷什么。\n",who,me);
    refuse_message  (me,who);
    return  1;

