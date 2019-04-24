// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("盐", ({"yan", "salt"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一包白盐。\n");
    set("unit", "包");
    set("value", 80);
    set("food_remaining", 20);
    set("food_supply", 1);
  }
}
