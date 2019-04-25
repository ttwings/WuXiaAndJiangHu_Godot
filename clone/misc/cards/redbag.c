// redbag.c 红包

inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(HIR "红包" NOR, ({"redbag", "bag"}));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", "一个装着压岁钱的红包，鼓鼓囊囊地不知包着什么好东西。\n\n    " HIR "过年好！！\n\n" NOR);
                set("value", 0);
        }
}

int is_container() { return 1; }
