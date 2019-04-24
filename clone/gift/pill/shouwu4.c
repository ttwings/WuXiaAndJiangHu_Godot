#include <ansi.h>
inherit __DIR__ "pill";

void create()
{ //4. 首乌丹	YEL	29000		15000	50		由何首乌混合数种珍贵药材所炼制的灵药。

        set_name(YEL "首乌丹" NOR, ({"shouwu dan", "shouwu", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", YEL "由何首乌混合数种珍贵药材所炼制的灵药。\n" NOR);
                set("unit", "颗");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 29000);
                set("force_point", 50);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
