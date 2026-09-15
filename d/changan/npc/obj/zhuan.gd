# // zhuan.c

#include <ansi.h>
# inherit ITEM;
extends Item
func create():
	set_name(CYN + "秦砖" + NOR,"qin zhuan");
	set_attr("long", "这是一块很古旧的秦砖。\n");
	set_attr("unit", "块");
	set_attr("value", 500);
	set_attr("weight", 100);

