// magenta1.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIM "银粉金鳞" NOR, ({"yinfen jinlin", "mudan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIM"这是一朵雍容华贵的粉色牡丹花，花朵婀娜多姿，委实令人心醉神迷。\n"NOR);
		set("unit", "束");
		set("value", 100);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower",1);
	}
	set_amount(1);
}
#include "/clone/flower/flower.h"
