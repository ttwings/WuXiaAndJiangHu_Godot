// medicine1.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY "黄帝内经" NOR, ({"huangdi neijing", "neijing", "jing"}));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是据传上古时代轩辕黄帝传世的医书。\n");
		set("value", 1500);
		set("material", "paper");
		set("skill", ([
								 "name":"medicine",
						 "exp_required":100,
							"jing_cost":10,
						   "difficulty":20,
							"min_skill":0,
							"max_skill":30]));
	}
}
