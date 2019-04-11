#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIC "灵性丹" NOR, ({ "lingxing dan", "lingxing", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "这是一颗灵性丹，据说吃了可以增加灵性。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "spi");
                set("gift_name", "先天灵性");
                set("gift_point", 75);
                set("gift_msg", HIM "你觉得身上发生了奇异的变化，但随即又平和了下来。\n" NOR);
        }
        setup();
}

