extends Item
func create():
	set_name("石凳", "seat")
	set_weight(20000);
	set_attr("long", "这是张大理石制的凳子。\n");
	set_attr("unit", "张");
	set_attr("material", "stone");
	set_attr("value", 2000);
	set_attr("no_get", 1);
	set_attr("amount", 30);