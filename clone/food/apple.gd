extends Food

func create():
	set_name("苹果","ping_guo")
	set_weight(40);
#	if (clonep())
#		set_default_object(__FILE__);
#	else {
	set_attr("long", "又大又脆的青苹果。\n");
	set_attr("unit", "颗");
	set_attr("value", 50);
	set_attr("food_remaining", 4);
	set_attr("food_supply", 30);
