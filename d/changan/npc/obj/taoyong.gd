# // taoyong.c
#include <ansi.h>
# inherit ITEM;
extends Item
func create():
	set_name(HIY + "陶俑" + NOR,"tao yong");
	set("long", "这是一个才出土不久陶俑。\n");
	set("unit", "个");
	set("value", 500);
	set("weight", 10);

