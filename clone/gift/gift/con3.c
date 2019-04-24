#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(NOR + YEL "洗髓再造仙丹" NOR, ({"xisui xiandan", "xisui",
                                                 "xiandan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", YEL "传说此丹乃是天宫中的神品，凡人吃了可以平增根骨。\n" NOR);
                set("unit", "颗");
                set("value", 100000);
                set("weight", 50);
                set("gift_type", "con");
                set("gift_name", "先天根骨");
                set("gift_point", 85);
                set("gift_msg", HIY "你浑身的骨骼登时哗啦啦的响个不停，可把你吓坏了，"
                                    "好在一会儿就停了下来，似乎筋骨更灵活了。\n" NOR);
        }
        setup();
}
