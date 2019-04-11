// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// by snowcat oct 15 1997

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("瓜子", ({"gua zi", "guazi", "zi", "seed"}));
  set_weight(100);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "一包喷香的瓜子。\n");
    set("eat_msg", "$N抓出一颗瓜子往嘴里一扔，啪地一声脆响。\n");
    set("unit", "包");
    set("value", 130);
    set("food_remaining", 25);
    set("food_supply", 1);
  }
}

