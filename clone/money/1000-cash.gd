# thousand.c

# inherit MONEY;
extends Money

func create():
	set_name("一千两银票", "thousand-cash");
	# if( clonep() )
		# set_default_object(__FILE__);
	# else {
	set_attr("money_id", "thousand-cash");
	set_attr("long", "一张面额值一千两银子的银票。\n");
	set_attr("unit", "叠");
	set_attr("base_value", 100000);
	set_attr("base_unit", "张");
	set_attr("base_weight", 3);
	set_amount(1);

