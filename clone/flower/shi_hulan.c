// shi_hulan.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIC "石斛兰" NOR, ({"shihu lan", "shi"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一朵花繁似锦，美艳绝伦的石斛兰，花瓣外观雅致绚丽，\n花朵中央有紫墨色的花晕，代表着“爱你永不变”。\n");
		set("unit", "束");
		set("value", 45);
		set("base_unit", "朵");
		set("base_weight", 100);
		set("flower", 1);
	}
	set_amount(1);
}
#include "flower.h"
