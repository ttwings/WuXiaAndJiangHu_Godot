# /inherit/item/money.c

# inherit COMBINED_ITEM;

extends Combined_item

class_name Money

func value() :
	return query_amount() * query("base_value")

func query_autoload() :
	return query_amount() + ""

func autoload(param:String):
	var amt;

	if( sscanf(param, "%d", amt)==1 ):
		set_amount(amt);
