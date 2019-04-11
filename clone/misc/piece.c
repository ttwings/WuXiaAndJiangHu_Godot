// cloth.c
//
// This is the basic equip for players just login.

#include <armor.h>

inherit ITEM;

void create()
{
        set_name("碎片", ({ "piece" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "堆");
        				set("long", "一堆不知道什么东西的碎片。\n");
        }
        setup();
}

