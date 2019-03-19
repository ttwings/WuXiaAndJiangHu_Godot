// zhuan.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(CYN"秦砖"NOR, ({"qin zhuan", "zhuan"}));
	set("long", "这是一块很古旧的秦砖。\n");
	set("unit", "块");
	set("value", 500);
	set("weight", 100);
}

