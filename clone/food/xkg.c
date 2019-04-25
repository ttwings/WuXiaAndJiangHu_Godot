// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// xkg.c 小苦瓜

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("小苦瓜", ({"xkg", "xiaokugua"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "一颗新鲜嫩绿的小苦瓜。\n");
    set("unit", "颗");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
