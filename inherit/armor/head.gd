# // head.c

#include <armor.h>

# inherit EQUIP;
extends Armor
func setup():
	# if( clonep(this_object()) ) :
	# 	return;
	set("armor_type", TYPE_HEAD);
	if( !query("armor_apply/dodge") && weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
