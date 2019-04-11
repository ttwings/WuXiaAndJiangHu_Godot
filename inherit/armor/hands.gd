# // hands.c

# #include <armor.h>

# inherit EQUIP;
extends Armor
class_name Hands

func setup():
	set("armor_type", TYPE_HANDS);
	if( !query("armor_apply/dodge") && weight() > 3000 ):
		set("armor_prop/dodge", - weight() / 3000 );

func _init():
	setup()