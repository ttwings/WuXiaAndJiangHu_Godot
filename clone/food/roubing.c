// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// created by snowcat on 4/9/1997
// roubing.c

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("羊肉饼", ({"roubing", "yang", "bing"}));
  set_weight(120);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一块烤得很香的羊肉肉饼。\n");
    set("unit", "块");
    set("value", 60);
    set("food_remaining", 3);
    set("food_supply", 120);
  }
}
