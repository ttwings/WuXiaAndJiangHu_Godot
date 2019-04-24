#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(HIW "白虎赐元丹" NOR, ({"baihu dan", "baihu", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIW "这是一颗纯白无暇的药丸，据说吃了可以增强膂力。\n" NOR);
                set("unit", "颗");
                set("value", 50000);
                set("weight", 50);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 65);
                set("gift_msg", HIY "突然间你只觉双臂几乎爆裂，充满了力量。\n" NOR);
        }
        setup();
}
