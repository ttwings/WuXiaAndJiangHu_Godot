# shurou.c
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("老鼠肉", ["laoshu rou", "rou"]);
	set_weight(300);
	set_attr("long", "一块鲜血淋漓肥的老鼠肉。\n");
	set_attr("unit", "块");
	set_attr("value", 200);
	set_attr("food_remaining", 4);
	set_attr("food_supply", 50);
	

