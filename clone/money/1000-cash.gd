# thousand.c

# inherit MONEY;
extends Money

func create():
	set_name("一千两银票", "thousand-cash");
	# if( clonep() )
		# set_default_object(__FILE__);
	# else {
	set("money_id", "thousand-cash");
	set("long", "一张面额值一千两银子的银票。\n");
	set("unit", "叠");
	set("base_value", 100000);
	set("base_unit", "张");
	set("base_weight", 3);
	set_amount(1);

