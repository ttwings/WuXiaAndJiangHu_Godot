#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(WHT "胆识丹" NOR, ({"danshi dan", "danshi", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", WHT "这是一颗胆识丹，听说吃了可以增加胆识。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "cor");
                set("gift_name", "先天胆识");
                set("gift_point", 75);
                set("gift_msg", HIM "你觉得身体发生了一些变化，但随即又平和了下来。\n" NOR);
        }
        setup();
}
