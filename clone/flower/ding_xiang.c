// dingxiang.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIW "丁香" NOR, ({"ding xiang", "ding"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","这是一朵水晶般的一串串白色丁香花，隐隐的散发着幽香。\n");
		set("unit", "束");
		set("value", 50);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower",1);
	}
	set_amount(1);
}

#include "flower.h"
