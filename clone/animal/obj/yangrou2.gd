# yangrou.c 羊肉
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("羊肉", ["yang rou", "lamb"]);
	set_weight(300);
	
	set_attr("long", "一块羔羊坐臀。\n");
	set_attr("unit", "块");
	set_attr("value", 80);
	set_attr("food_remaining", 4);
	set_attr("food_supply", 50);
	

