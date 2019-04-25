# yangpi.c 羊皮
# Last Modified by winder on Aug. 1 2002

#include <armor.h>
extends Armor;

func create():

	set_name("羊皮", ["yang pi", "pi", "lamb skin"]);
	set_weight(3000);
	
	set("unit", "块");
	set("material", "fur");
	set("value", 400);
	set("armor_prop/armor", 3);
	
	setup();

