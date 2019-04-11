// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// xbc.c 小白菜

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("小白菜", ({"xbc", "xiaobaicai"}));
   set_weight(40);
   if (clonep())
     set_default_object(__FILE__);
   else {
                set("long", "一颗新鲜可人的小白菜。\n");
                set("unit", "颗");
     set("value", 80);
     set("food_remaining", 4);
     set("food_supply", 30);
   }
}
