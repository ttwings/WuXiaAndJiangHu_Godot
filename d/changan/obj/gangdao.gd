# // gangdao.c

#include <weapon.h>
# inherit BLADE;

extends Weapon

func create():
	set_name("钢刀", "blade");
	set_weight(7000);
	set_attr("unit", "柄");
	set_attr("long", "这是一柄亮晃晃的钢刀，普通官兵的常备武器。\n");
	set_attr("value", 1000);
	set_attr("material", "steel");
	set_attr("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
	set_attr("unwield_msg", "$N将手中的$n插回刀鞘。\n");
	init_blade(20);
	setup();
