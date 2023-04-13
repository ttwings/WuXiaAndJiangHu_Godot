# combined_item.c
# Modified by zeratul,2000.1.29

#include <dbase.h>
#include <name.h>

# inherit F_CLEAN_UP;
# inherit F_DBASE;
# inherit F_MOVE;
# inherit F_NAME;

extends Item
#############################  combined  #################################

var amount;

func query_amount() :
	return amount;

func destruct_me() :
	destruct(this_object())

func set_amount(v:int):
	if( v < 0 ):
		error("combine:set_amount less than 1.\n");
# //	if( v==0 ) destruct(this_object()); 
	if( v == 0 ) :
		# ::move(VOID_OB);
		call_out("destruct_me", 1);
	else :
		amount = v;
		this_object().set_weight(v * int(query("base_weight")));

func add_amount(v:int) :
	set_amount(amount+v)

func short(raw=true):
	if (query_amount()>1):
		return chinese_number(query_amount()) + query("base_unit") + super.short();
	else:
		return super.short();

func move(dest,silent:int = 0):
	var env
	var inv;
	var i
	var total;
	var file;

	if( super.move(dest, silent) ):
#		if( living(env = environment()) ) {
		env = environment();
		file = base_name(this_object());
		inv = all_inventory(env);
		total = query_amount();
		# for(i=0; i<sizeof(inv); i++) :
		for i in range(sizeof(inv)):
			if( inv[i]==this_object() ) :
				continue;
			if( base_name(inv[i])==file ) :
				total += inv[i].query_amount();
				destruct(inv[i]);
		set_amount(total);
		return 1;
