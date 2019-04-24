// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("白玉酒盏", ({"jiu zhan", "zhan", "cup"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一个淡白玉的小酒盏。\n");
                set("unit", "个");
                set("value", 500);
                set("max_liquid", 10);
        }

        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                                 "type":"alcohol",
                                 "name":"女儿红",
                            "remaining":10,
                          "drunk_apply":5,
        ]));
}
