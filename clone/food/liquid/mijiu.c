// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// wine.c 江米酒

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("江米酒", ({"mijiu"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "南方人爱吃的江米酒。\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 6);
                set("food_supply", 20);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                                 "type":"alcohol",
                                 "name":"江米酒",
                          "drunk_apply":10,
        ]));
}
