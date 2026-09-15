# goupi.c
# Last Modified by winder on Aug. 1 2002

#include <ansi.h>
#include <armor.h>

extends Armor;

func create():

	set_name(YEL +  "狗皮" + NOR, ["gou pi", "pi"]);
	set_weight(5000);
	set_attr("unit", "块");
	set_attr("material", "fur");
	set_attr("value", 100);
	set_attr("armor_prop/armor", 1);
	
	setup();

