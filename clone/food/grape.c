// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

inherit ITEM;
inherit F_FOOD;

void create()
{
  set_name("水晶葡萄", ({"pu tao", "grape", "putao"}));
  set_weight(40);
  if (clonep())
    set_default_object(__FILE__);
  else
  {
    set("long", "水灵灵的葡萄象一颗颗紫色的水晶球。\n");
    set("unit", "把");
    set("value", 80);
    set("food_remaining", 4);
    set("food_supply", 30);
  }
}
