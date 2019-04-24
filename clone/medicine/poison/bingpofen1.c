// bingpofen1.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIB "点燃的冰魄粉" NOR, ({"bingpo fen", "fen", "bingpo"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一包透着阴深冷气的毒粉。已经点燃，可以涂(tu)在兵器上了。\n");
		set("unit", "些");
		set("base_value", 5000);
		set("base_unit", "包");
		set("base_weight", 30);
		set("drug_color", "" HIB "阴气森森" NOR "");
		set("pour_type", "bing_poison");
	}
	set_amount(1);
}

#include "poison1.h";
