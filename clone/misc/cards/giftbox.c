// giftbox.c 礼品盒

inherit ITEM;
#include <ansi.h>
void create()
{
        set_name(HIR"礼品盒"NOR, ({ "giftbox", "box" }));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", "一盒礼品盒。盒里装着巫师的贺礼。\n\n    "HIR"节日快乐！！\n\n"NOR);
                set("value", 0);
        }
}

int is_container() { return 1; }

