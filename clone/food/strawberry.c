// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// xueli.c 雪梨

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("草莓", ({"cao mei", "strawberry", "caomei"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "鲜红的草莓。\n");
    set("unit", "把");
    set("value", 120);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
