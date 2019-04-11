#include <ansi.h>
inherit __DIR__"pill";

void create()
{//2. 百年雪莲	CYN	30000		15000	5		产于大雪山之上的珍贵药材，服用后可提升轻功等级。

        set_name(CYN "百年雪莲" NOR, ({ "bainian xuelian",  "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
								set("long", CYN "产于大雪山之上的珍贵药材，服用后可提升轻功等级。\n" NOR);
								set("unit", "株");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 30000);
                set("force_point", 5);
                set("pill_msg1", HIW "你只感到清凉之意散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只觉灵台处清欣无比，精力得到了完全的补充。\n" NOR);
        }
        setup();
}
