// head.c -脑袋
#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(RED "头颅" NOR, ({"head"}));
    set_weight(300);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("unit", "颗");
        set("value", 10);
        set("long", RED "一颗鲜血淋淋的首级，须发散乱，余血正缓缓渗出。\n" NOR);
    }
}
