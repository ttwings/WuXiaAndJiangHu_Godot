# /*  <SecCrypt CPL V3R05>  */
 
#  by  snowcat  on  7/5/1997  
# inherit  NPC;
extends Npc

func random2(i):
    return  randi()  %  i;

func create():
    set_name("赛龟", "sai  gui");
    set("race",  "野兽");
    set("gender",  "雄性");
    set("age",  2);
    set("long",  "一只慢腾腾的赛龟。\n");
    set("attitude",  "friendly");
    set("str",  20+random2(2));
    set("spi",  20+random2(2));
    set("cor",  20+random2(2));
    set("con",  20);
    set("cor",  20);
    set("cps",  20);
    set("dex",  20);
    set("per",  20);
    set("limbs",  ["头部",  "爪子",  "尾巴" ]);
    set("verbs",  ["bite"]);

    setup();

