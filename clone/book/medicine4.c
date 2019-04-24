// medicine4.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY "子午针灸经" NOR, ({"ziwu zhenjiujing", "ziwu", "jing"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是蝶谷医仙胡青牛所著医书。\n");
		set("value", 15000);
		set("material", "paper");
		set("skill", ([
								 "name":"acupuncture",
						 "exp_required":100,
							"jing_cost":10,
						   "difficulty":20,
							"max_skill":50]));
	}
}
