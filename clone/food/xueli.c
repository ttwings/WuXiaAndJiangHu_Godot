// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// xueli.c 雪梨

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("雪梨", ({"xue li", "xueli", "li"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "这种雪梨只生长于雪山极寒之地。\n");
    set("unit", "颗");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
