#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(YEL "定力丹" NOR, ({"dingli dan", "dingli", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", WHT "这是一颗定力丹，据说吃了可以增加定力。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "cps");
                set("gift_name", "先天定力");
                set("gift_point", 75);
                set("gift_msg", HIM "你觉得身上发生了奇异的变化，但随即又平和了下来。\n" NOR);
        }
        setup();
}
