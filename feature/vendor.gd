# vendor.c

#include <dbase.h>

func buy_object(me:Char,what:String):
	var ob;
	if( stringp(ob = query("vendor_goods/" + what)) ):
		return ob.query("value");
	else:
		return 0;

func compelete_trade(me:Char, what:String):
	var ob_file;
	var ob;

	if( stringp(ob_file = query("vendor_goods/" + what)) ):
		ob = new(ob_file);
		ob.move(me);
		message_vision("$N向$n买下一" + ob.query("unit") + ob.query("name") + "。\n",
			me, this_object() );

func price_string(v:int):
	if( v%10000 == 0 ):
		return chinese_number(v/10000) + "两黄金";
	if( v%100 == 0 ):
		return chinese_number(v/100) + "两白银";
	return chinese_number(v) + "文铜板";

func do_vendor_list(arg:String):
	var goods;
	var list
	var name;
	var i;
	goods = query("vendor_goods")
	if( !mapp(goods) ) :
		return 0;
	if( arg && !this_object().id(arg) ) :
		return 0;
	name = keys(goods);
	list = "你可以购买下列这些东西：\n";
	for(i=0; i<sizeof(name); i++):
		list += sprintf("%-30s：%s\n",
			goods[name[i]].query("name") + "(" +
			goods[name[i]].query("id") + ")",
			price_string(goods[name[i]].query("value")) );
	write(list);
	return 1;	
