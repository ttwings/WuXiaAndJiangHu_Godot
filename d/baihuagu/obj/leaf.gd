extends Item
#include <ansi.h>
# inherit ITEM;
func create():
	set_name(HIM + "桃花" + NOR,"leaf", "flower");
	set_weight(80);
	# if (clonep())
	# 	set_default_object(__FILE__);
	# else {
	set("long", HIM + "这是一枝娇艳的桃花。\n" + NOR);
	set("unit", "枝");
	set("value", 100);

func _init():
	create()	
