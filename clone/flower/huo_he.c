// huohe.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIR "火鹤" NOR, ({"huo he", "huo"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一朵娇艳火红的火鹤，热情奔放，吉利，充满喜庆、祥和、希望。\n");
		set("unit", "束");
		set("value", 75);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower", 1);
	}
	set_amount(1);
}
#include "flower.h"
