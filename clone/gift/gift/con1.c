#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(WHT "壮骨粉" NOR, ({"zhuanggu fen", "zhuanggu", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", WHT "这是一包灰黑色的药粉，据说吃了可以增强根骨。\n" NOR);
                set("unit", "包");
                set("value", 10000);
                set("weight", 50);
                set("gift_type", "con");
                set("gift_name", "先天根骨");
                set("gift_point", 40);
                set("gift_msg", HIY "你浑身的骨骼登时哗啦啦的响个不停，可把你吓坏了，"
                                    "好在一会儿就停了下来，似乎筋骨更灵活了。\n" NOR);
        }
        setup();
}
