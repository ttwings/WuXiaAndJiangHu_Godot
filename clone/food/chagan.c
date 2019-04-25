// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("五香茶干", ({"cha gan", "gan"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一碟五香茶干。\n");
    set("unit", "碟");
    set("value", 120);
    set("food_remaining", 6);
    set("food_supply", 25);
  }
}
