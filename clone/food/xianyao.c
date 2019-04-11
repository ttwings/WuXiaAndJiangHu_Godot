// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// xianyao.c        

inherit ITEM;
inherit F_FOOD;

void create()
{
  string *names = ({
    "龙肝",
    "凤髓",
    "熊掌",
    "猩唇",
    });
  string *ids = ({
    "long gan",
    "feng sui",
    "xiong zhang",
    "xing chun",
    });
  int i = random(4);

  set_name(names[i],({ids[i]}));
  set_weight(300);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "金碗");
    set("value", 10000);
    set("food_remaining", 20);
    set("food_supply", 100);
    set("no_get",1);
    set("no_drop",1);
    set("no_sell",1);
  }
  set("long", "一金碗天上才有的仙肴珍馐－－"+names[i]+"。\n");
}

