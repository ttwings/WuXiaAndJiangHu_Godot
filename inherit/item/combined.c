// combined_item.c
// Modified by zeratul,2000.1.29

#include <dbase.h>
#include <name.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

static int amount;

void setup()
{
}

int query_amount() { return amount; }

private void destruct_me() { destruct(this_object()); }

void set_amount(int v)
{
	if( v < 0 ) error("combine:set_amount less than 1.\n");
//	if( v==0 ) destruct(this_object()); 
	if( v==0 ) {
		::move(VOID_OB);
		call_out("destruct_me", 1);
	}
	else {
		amount = v;
		this_object()->set_weight(v * (int)query("base_weight"));
	}
}

void add_amount(int v) { set_amount(amount+v); }

string short()
{
	if (query_amount()>1)
	return chinese_number(query_amount()) + query("base_unit")
		+ ::short();
	else
	return ::short();
}

varargs int move(mixed dest, int silent)
{
	object env, *inv;
	int i, total;
	string file;

	if( ::move(dest, silent) ) {
//		if( living(env = environment()) ) {
		env = environment();
		file = base_name(this_object());
		inv = all_inventory(env);
		total = (int)query_amount();
		for(i=0; i<sizeof(inv); i++) {
			if( inv[i]==this_object() ) continue;
			if( base_name(inv[i])==file ) {
				total += (int)inv[i]->query_amount();
				destruct(inv[i]);
			}
		}
		set_amount(total);
//		}
		return 1;
	}
}

