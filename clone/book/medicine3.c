// medicine3.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY "王叔和脉经" NOR, ({"wangshuhe maijing", "maijing", "jing"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本王叔和脉。年代久远，纸质破旧。\n");
		set("value", 1500);
		set("material", "paper");
		set("skill", ([
								 "name":"medicine",
						 "exp_required":2000,
							"jing_cost":10,
						   "difficulty":20,
							"min_skill":60,
							"max_skill":100]));
	}
}
