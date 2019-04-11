// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("花生豆", ({"huasheng", "dou"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碟花生豆．\n");
                set("unit", "碟");
                set("value", 20);
                set("food_remaining", 4);
                set("food_supply", 10);
        }
}

