# // mi.c 蜜
# inherit ITEM;
extends Item
func create():
	set_name("蜂蜜", "mi");
	set_weight(400);
	# if (clonep())
	# 	set_default_object(__FILE__);
	# else
	set_attr("long", "一罐玉蜂的蜂蜜，散发出诱人的香味。\n");
	set_attr("unit", "罐");
	set_attr("value",0);
	set_attr("no_give", "这样东西还是不要给别人的好。\n");
	set_attr("no_put",  "呀，小心撒了。\n"); 

# func _init():
# 	create()
