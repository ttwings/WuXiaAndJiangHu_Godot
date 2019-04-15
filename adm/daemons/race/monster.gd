# monster.c
# Last Modified by winder on Aug. 1 2002

#include <race/monster.h>

func setup_monster(ob):
	var my;

	my = ob.query_entire_dbase();

	my["unit"] = "只";
	
	if( undefinedp(my["gender"]) ) :
		my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) :
		my["age"] = random(80) + 5;

	if( undefinedp(my["str"]) ) :
		my["str"] = random(41) + 10;
	if( undefinedp(my["int"]) ) :
		my["int"] = random(41) + 10;
	if( undefinedp(my["per"]) ) :
		my["per"] = random(11) + 10;
	if( undefinedp(my["con"]) ) :
		my["con"] = random(41) + 10;
	if( undefinedp(my["dex"]) ) :
		my["dex"] = random(41) + 10;

	if( undefinedp(my["max_jing"]) ) :
		if( my["age"] <= 3 ) :
			my["max_jing"] = 50;
		elif( my["age"] <= 10 ) :
			my["max_jing"] = 50 + (my["age"] - 3) * 30;
		elif( my["age"] <= 60 ) :
			my["max_jing"] = 260 + (my["age"] - 10) * 5;
		else :
			my["max_jing"] = my["max_jing"] = 510 + (my["age"] - 60);
	}
	if( undefinedp(my["max_qi"]) ) :
		if( my["age"] <= 10 ) :
			my["max_qi"] = 100;
		elif( my["age"] <= 30 ) :
			my["max_qi"] = 100 + (my["age"] - 10) * 30;
		else :
			my["max_qi"] = my["max_qi"] = 700 + (my["age"] - 30) * 10;
	
	#	NOTE: monster has no initial limbs defined, you must define it yourself.
	#	ob.init_limbs(LIMBS);
	if( !ob.query_weight() ) :
		ob.set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);


