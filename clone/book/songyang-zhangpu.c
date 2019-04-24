// songyang-zhangpu.c 大嵩阳掌谱
// Last Modified by Winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name(RED "大嵩阳掌谱" NOR, ({
									   "songyang zhangpu",
									   "zhangpu",
								   }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一张麻纸小册，上面好象还有一些小人挥舞拳脚的图形。\n", );
		set("value", 0);
		set("material", "paper");
		set("skill", ([
								 "name":"songyang-strike",
						 "exp_required":10000,
							"jing_cost":30,
						   "difficulty":20,
							"max_skill":80]));
	}
}
