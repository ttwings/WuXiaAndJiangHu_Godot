# shurou.c
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("老鼠肉", ["laoshu rou", "rou"]);
	set_weight(300);
	set("long", "一块鲜血淋漓肥的老鼠肉。\n");
	set("unit", "块");
	set("value", 200);
	set("food_remaining", 4);
	set("food_supply", 50);
	

