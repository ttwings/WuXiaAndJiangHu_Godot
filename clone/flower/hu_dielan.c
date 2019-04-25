// hu_dielan.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIM "蝴蝶兰" NOR, ({"hudie lan", "hu"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一朵灿烂的蝴蝶兰，花形似彩蝶，花姿优美动人，隐喻着“我爱你”之意。\n");
		set("unit", "束");
		set("value", 100);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower", 1);
	}
	set_amount(1);
}
#include "flower.h"
