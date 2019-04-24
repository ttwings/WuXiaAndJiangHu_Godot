// jin_yucao.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIY "金鱼草" NOR, ({"jinyu cao", "jin"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一朵花型别致，似咧嘴微笑的金鱼草，象征有金有余，鸿运当头。\n");
		set("unit", "束");
		set("value", 25);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower", 1);
	}
	set_amount(1);
}
#include "flower.h"
