#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(HIY "增慧丹" NOR, ({"zenghui dan", "zenghui", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIY "这是一颗通体金黄的药丸，据说吃了可以增强悟性。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "int");
                set("gift_name", "先天悟性");
                set("gift_point", 40);
                set("gift_msg", HIG "一股火热蓦然从脑中升起，"
                                    "你头痛欲裂，恰在此时一股清凉之意油然而起，顿感舒泰无比。\n" NOR);
        }
        setup();
}
