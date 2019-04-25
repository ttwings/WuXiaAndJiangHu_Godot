// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// created by snowcat on 4/9/1997
// jiunang.c 羊皮大酒囊

inherit ITEM;
inherit F_LIQUID;

void create()
{
  set_name("羊皮大酒囊", ({"jiunang", "wineskin", "skin"}));
  set_weight(800);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一个用来装羊奶酒的大酒囊，大概装得十来升的酒。\n");
    set("unit", "个");
    set("value", 100);
    set("max_liquid", 20);
  }

  set("liquid", ([
                            "type":"alcohol",
                            "name":"羊奶酒",
                       "remaining":20,
                    "drunk_supply":8,
  ]));
}
