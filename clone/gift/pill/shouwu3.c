#include <ansi.h>
inherit __DIR__ "pill";

void create()
{ //3. 千年何首乌	HIW	40000		20000	10		产于极北森林之上的珍贵药材，服用后可提升招架等级。

        set_name(HIW "千年何首乌" NOR, ({"qiannian heshouwu", "heshouwu", "shouwu"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIW "产于极北森林之中的珍贵药材，服用后可提升招架等级。\n" NOR);
                set("unit", "支");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 40000);
                set("force_point", 10);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
