# // taoyong.c
#include <ansi.h>
# inherit ITEM;
extends Item
func create():
	set_name(HIY + "陶俑" + NOR,"tao yong");
	set_attr("long", "这是一个才出土不久陶俑。\n");
	set_attr("unit", "个");
	set_attr("value", 500);
	set_attr("weight", 10);

