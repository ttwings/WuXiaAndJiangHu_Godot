# /*  <SecCrypt CPL V3R05>  */
 
#  by  snowcat  on  7/5/1997  
# inherit  NPC;
extends Npc

func random2(i):
    return  randi()  %  i;

func create():
    set_name("赛龟", "sai  gui");
    set_attr("race",  "野兽");
    set_attr("gender",  "雄性");
    set_attr("age",  2);
    set_attr("long",  "一只慢腾腾的赛龟。\n");
    set_attr("attitude",  "friendly");
    set_attr("str",  20+random2(2));
    set_attr("spi",  20+random2(2));
    set_attr("cor",  20+random2(2));
    set_attr("con",  20);
    set_attr("cor",  20);
    set_attr("cps",  20);
    set_attr("dex",  20);
    set_attr("per",  20);
    set_attr("limbs",  ["头部",  "爪子",  "尾巴" ]);
    set_attr("verbs",  ["bite"]);

    setup();

