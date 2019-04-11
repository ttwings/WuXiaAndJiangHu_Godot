#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(WHT "玄武铸骨丹" NOR, ({ "xuanwu dan", "xuanwu", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "这是一颗坚硬无比黑色丹药，据说吃了可以增强根骨。\n" NOR);
                set("unit", "颗");
                set("value", 50000);
                set("weight", 50);
                set("gift_type", "con");
                set("gift_name", "先天根骨");
                set("gift_point", 65);
                set("gift_msg", HIY "你浑身的骨骼登时哗啦啦的响个不停，可把你吓坏了，"
				"好在一会儿就停了下来，似乎筋骨更灵活了。\n" NOR);
        }
        setup();
}

