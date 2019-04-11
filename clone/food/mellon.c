// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("哈密瓜", ({"hami gua", "mellon","gua"}));
   set_weight(40);
   if (clonep())
     set_default_object(__FILE__);
   else {
                set("long", "又香又甜的哈密瓜。n");
                set("unit", "颗");
     set("value", 100);
     set("food_remaining", 4);
     set("food_supply", 30);
   }
}
