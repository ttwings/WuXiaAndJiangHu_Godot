// wa.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIC"汉瓦"NOR, ({"han wa", "wa"}));
	set("long", "这是一片珍贵的汉瓦。\n");
	set("unit", "片");
	set("value", 500);
	set("weight", 10);
}

