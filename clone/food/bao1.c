// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// dumpling.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("猪肉馅包子", ({"zhurou bao", "bao"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一个香喷喷、热腾腾的猪肉馅灌汤包子。\n");
                set("unit", "个");
                set("value", 25);
                set("food_remaining", 2);
                set("food_supply", 40);
        }
}

