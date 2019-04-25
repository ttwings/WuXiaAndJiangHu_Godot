// qiu_haitang.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIY "秋海棠" NOR, ({"qiu haitang", "qiu"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一朵秋海棠，又名断肠花，象征苦恋。当人们爱情遇到波折、男\n女离别时，常以秋海棠自喻。 \n");
		set("unit", "束");
		set("value", 35);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower", 1);
	}
	set_amount(1);
}
#include "flower.h"
