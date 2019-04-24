// jueqingwhip.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit F_UNIQUE;
inherit WHIP;

void create()
{
        set_name("情丝", ({"silk whip", "whip"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一条蓝色的长带，细看由无数细如毛发的长丝聚成，虽轻若无物，却无孔不入。\n");
                set("unit", "条");
                set("value", 12000);
                set("wield_msg", "$N左手轻扬，一条蓝色绸带忽地甩了出来。\n");
                set("unwield_msg", "$N把手中$n缠回腰间。\n");
                set("weapon_prop/courage", 5);
        }
        init_whip(60);
        set("is_monitored", 1);
        setup();
}
