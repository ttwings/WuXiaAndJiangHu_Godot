// yu_jinxiang.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIY "郁金香" NOR, ({"yu jinxiang", "jinxiang"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","这是一朵金黄色的郁金香，花朵丰润美丽，是胜利美好的象征。\n");
		set("unit", "束");
		set("value", 25);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower",1);
	}
	set_amount(1);
}
#include "flower.h"
