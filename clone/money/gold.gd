# gold.c
#include <ansi.h>
# inherit MONEY;
extends Money
func create():
	set_name(YEL + "黄金" + NOR, ["gold", "ingot", "gold_money"]);
	# if( clonep() )
	# 	set_default_object(__FILE__);
	# else {
	set_attr("money_id", "gold");
	set_attr("long", "黄澄澄的金子，人见人爱的金子，啊～～金子！\n");
	set_attr("unit", "些");
	set_attr("base_value", 10000 );
	set_attr("base_unit", "两");
	set_attr("base_weight", 37);
	set_amount(1);

