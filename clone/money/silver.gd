# silver.c
#include <ansi.h>
# inherit MONEY;
extends Money

func create():
	set_name(HIW + "白银" + NOR, ["silver", "ingot", "silver_money"]);
	# if( clonep() )
		# set_default_object(__FILE__);
	# else {
	set_attr("money_id", "silver");
	set_attr("long", "白花花的银子，人见人爱的银子。\n");
	set_attr("unit", "些");
	set_attr("base_value", 100);
	set_attr("base_unit", "两");
	set_attr("base_weight", 37);
	set_amount(1);

