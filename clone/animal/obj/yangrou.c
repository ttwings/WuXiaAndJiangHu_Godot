# yangrou.c 烤羊腿
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("烤羊腿", ["kao yangtui", "yangtui"]);
	set_weight(300);
	
	set("long", "一只烤得香喷喷的羊腿。\n");
	set("unit", "只");
	set("value", 100);
	set("food_remaining", 4);
	set("food_supply", 60);
	

