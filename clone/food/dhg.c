// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// dhg.c 大黄瓜

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("大黄瓜", ({"dhg", "dahuanggua"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一条新鲜嫩绿的大黄瓜。\n");
    set("unit", "条");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
