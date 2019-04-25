# turou.c 野兔肉
# Last Modified by winder on Aug. 1 2002

extends Food;
# inherit F_FOOD;

func create():

	set_name("兔肉", ["tu rou", "tu"]);
	set_weight(300);
	
	set("long", "一块鲜血淋漓肥的野兔肉。\n");
	set("unit", "块");
	set("value", 50);
	set("food_remaining", 4);
	set("food_supply", 50);
	#		set("food_race","野兽");
	

