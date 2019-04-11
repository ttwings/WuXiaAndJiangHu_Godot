#include <ansi.h>
inherit __DIR__"pill";

void create()
{//1.  高山灵芝	CYN	20000		10000	3		产于高山上的珍贵药材，服用后可提升内功等级。

        set_name(CYN "高山灵芝" NOR, ({ "gaoshan lingzhi", "lingzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
								set("long", CYN "产于高山上的珍贵药材，服用后可提升内功等级。\n" NOR);
								set("unit", "株");
                set("value", 10000);
                set("weight", 300);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 20000);
                set("force_point", 3);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
