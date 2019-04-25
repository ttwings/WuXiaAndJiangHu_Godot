#include <ansi.h>
inherit __DIR__ "pill";

void create()
{ //5.  百年参心丹	HIR	39000		20000	100		由百年人参混合数种珍贵药材所炼制的灵药。

        set_name(HIR "百年参心丹" NOR, ({"bainian shenxindan", "renshen", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIR "由百年人参混合数种珍贵药材所炼制的灵药。\n" NOR);
                set("unit", "颗");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "force");
                set("pill_point", 39000);
                set("force_point", 100);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
