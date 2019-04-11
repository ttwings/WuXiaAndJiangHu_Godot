// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("鲜肉水饺", ({"shui jiao", "jiao", "dumpling"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一碗热气腾腾的鲜肉水饺。\n");
    set("unit", "碗");
    set("value", 200);
    set("food_remaining", 5);
    set("food_supply", 35);
  }
}
