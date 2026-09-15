# banjiu-rou.c 斑鸠肉
# Last Modified by winder on Aug. 1 2002

# extends Item;
# inherit F_FOOD;
extends Food

func create():

	set_name("斑鸠肉", ["banjiu rou", "bird meat"]);
	set_weight(100);
	set_attr("long", "一只死的斑鸠。\n");
	set_attr("unit", "只");
	set_attr("value", 20);
	set_attr("food_remaining", 1);
	set_attr("food_supply", 40);
	#		set_attr("food_race","野兽");
	

