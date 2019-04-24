// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  string name = "油炝大虾";
  set_name(name, ({"youqiang daxia", "daxia", "xia"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一盘令人垂涎的" + name + "。\n");
    set("unit", "盘");
    set("value", 250);
    set("food_remaining", 5);
    set("food_supply", 25);
  }
}
