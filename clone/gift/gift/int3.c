#include <ansi.h>
inherit __DIR__ "gift";

void create()
{
        set_name(HIW "神恩通慧仙丹" NOR, ({"tonghui xiandan", "tonghui",
                                           "xiandan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIW "传说此丹乃是天宫中的神品，凡人吃了可以平增悟性。\n" NOR);
                set("unit", "颗");
                set("value", 100000);
                set("weight", 50);
                set("gift_type", "int");
                set("gift_name", "先天悟性");
                set("gift_point", 85);
                set("gift_msg", HIG "一股火热蓦然从脑中升起，"
                                    "你头痛欲裂，恰在此时一股清凉之意油然而起，顿感舒泰无比。\n" NOR);
        }
        setup();
}
