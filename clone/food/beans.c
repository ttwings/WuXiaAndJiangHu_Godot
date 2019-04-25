// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// beans.c 豆豆

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("豆豆", ({"beans", "doudou"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一把可爱的小豆豆。\n");
    set("unit", "把");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
