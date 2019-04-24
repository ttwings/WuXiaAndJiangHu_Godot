#include <ansi.h>
inherit __DIR__ "pill";

void create()
{ //6. 千年雪莲膏	HIM	49000		25000	150		由千年雪莲混合数种珍贵药材所炼制的灵药。

        set_name(HIM "千年雪莲膏" NOR, ({"qiannian xueliangao", "xuelian", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", HIM "由千年雪莲混合数种珍贵药材所炼制的灵药。\n" NOR);
                set("unit", "盒");
                set("value", 25000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 49000);
                set("force_point", 150);
                set("pill_msg1", HIW "你只感到清凉之意散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只觉灵台处清欣无比，精力得到了完全的补充。\n" NOR);
        }
        setup();
}
