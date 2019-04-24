#include <ansi.h>
inherit __DIR__ "pill";

void create()
{ //5. 百年首乌丹	CYN	39000		20000	100		由百年何首乌混合数种珍贵药材所炼制的灵药。

        set_name(CYN "百年首乌丹" NOR, ({"bainian shouwudan", "shouwu", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", CYN "由百年何首乌混合数种珍贵药材所炼制的灵药。\n" NOR);
                set("unit", "颗");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 39000);
                set("force_point", 100);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
