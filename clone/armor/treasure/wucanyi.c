// wuchangyi.c
//
#include <armor.h>

inherit CLOTH;
inherit F_UNIQUE;

void create()
{
        set_name("乌蚕衣", ({"wucan yi", "cloth"}));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "件");
                set("material", "silk");
                set("value", 50000);
                set("armor_prop/armor", 200);
                set("long",
"这一件刀枪不入的宝衣，是用大雪山的上乌蚕蚕丝织成的。整
件乌蚕衣只是两块料子，剪刀也剪不烂，只得前一块、后一块
的扣在一起。");
        }
        setup();
}
