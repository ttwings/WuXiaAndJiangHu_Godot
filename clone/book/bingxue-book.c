// Last Modified by winder on Jul. 15 2001
// bingxue-book.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIW "冰雪心法" NOR, ({"bingxue-book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本学冰雪心法的书。\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
								 "name":"bingxue-xinfa",
						 "exp_required":50000,
							"jing_cost":20,
						   "difficulty":20,
							"max_skill":100,
							"min_skill":10]));
	}
}
int query_autoload() { return 1; }
