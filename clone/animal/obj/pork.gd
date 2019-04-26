# pork.c 猪肉
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("小猪耳朵", ["zhu erduo", "zhu rou", "pork"]);
	set_weight(300);
	set("long", "一块小猪耳朵肉。\n");
	set("unit", "块");
	set("value", 80);
	set("food_remaining", 4);
	set("food_supply", 20);
	

