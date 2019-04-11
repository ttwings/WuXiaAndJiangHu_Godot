#include <ansi.h>
inherit __DIR__"pill";

void create()
{//3.  千年人参	HIY	40000		20000	10		产于高山上的珍贵药材，服用后可提升基本内功等级。

        set_name(HIY "千年人参" NOR, ({ "qiannian renshen",  "renshen", "shen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
								set("long", HIY "产于高山上的珍贵药材，服用后可提升基本内功等级。\n" NOR);
								set("unit", "株");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "force");
                set("pill_point", 40000);
                set("force_point", 10);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
