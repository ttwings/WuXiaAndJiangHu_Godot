// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// created by snowcat on 4/9/1997
// egg.c

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("水煮蛋", ({"egg", "dan"}));
  set_weight(60);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一只煮熟的鸡蛋。\n");
    set("unit", "只");
    set("value", 50);
    set("food_remaining", 1);
    set("food_supply", 60);
  }
}
