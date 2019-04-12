# // boots.c

# #include <armor.h>

# inherit EQUIP;
extends  Armor

func setup():
	set("armor_type", TYPE_BOOTS);
	if( !query("armor_apply/dodge") &&	weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );
