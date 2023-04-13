# /*  <SecCrypt CPL V3R05>  */
 
#  created  7/6/1997  by  snowcat
#include  <ansi.h>

# inherit  NPC;
extends Npc
var room  =  0;

func create():
    set_name("     ", "gui  tong");
    set("gender",  "  ");
    set("age",  13);
    set("per",  30);
    set("long",  "һλ     Ĺ    \n");
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


func init():
    super.init();
    add_action("do_fight",  "fight");
    add_action("do_kill",  "kill");
    if  (room  ==  0):
        room  =  environment(this_object());


func refuse_message(me,  who):
    message_vision("$N˵      ɱ$N         \n",me,who);


func do_fight(arg):
    var who  =  this_player();
    var me  =  this_object();

    if  (arg  &&  present(arg,environment(who))==me):
        message_vision("$N        ۣ   $n    \n",who,me);
        refuse_message(me,who);
        return  1;
    return  0;


func  do_kill(arg):
    var who  =  this_player();
    var me  =  this_object();

    if  (arg  &&  present(arg,environment(who))==me):
        message_vision("$N        ۣ  ɱ$n  \n",who,me);
        refuse_message(me,who);
        return  1;
    return  0;

