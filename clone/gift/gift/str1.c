#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIG "神力丸" NOR, ({ "shenli wan", "shenli", "wan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "这是一颗通体浑圆的药丸，据说吃了可以增强膂力。\n" NOR);
                set("unit", "颗");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 40);
                set("gift_msg", HIY "突然间你只觉双臂几乎爆裂，充满了力量。\n" NOR);
        }
        setup();
}

