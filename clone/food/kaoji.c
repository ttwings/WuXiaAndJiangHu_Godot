// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// chicken.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("烤鸡", ({"chicken"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一只香喷喷的烤鸡。\n");
                set("unit", "只");
                set("value", 100);
                set("food_remaining", 3);
                set("food_supply", 30);
        }
}
