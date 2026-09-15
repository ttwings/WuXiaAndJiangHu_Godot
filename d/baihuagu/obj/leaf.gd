extends Item
#include <ansi.h>
# inherit ITEM;
func create():
	set_name(HIM + "桃花" + NOR,"leaf");
	set_weight(80);
	# if (clonep())
	# 	set_default_object(__FILE__);
	# else {
	set_attr("long", HIM + "这是一枝娇艳的桃花。\n" + NOR);
	set_attr("unit", "枝");
	set_attr("value", 100);

# func _init():
# 	create()	
