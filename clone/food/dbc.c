// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// dbc.c 大白菜

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("大白菜", ({"dbc", "dabaicai"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一颗新鲜可人的大白菜。\n");
    set("unit", "颗");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
