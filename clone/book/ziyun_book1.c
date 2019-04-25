// ziyun_book1.c  紫氲正谱
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIM "紫氲正谱" NOR, ({"ziyun_book", "book"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long",
			"这是一本薄薄的册页。\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
								 "name":"ziyunyin", // name of the skill
						 "exp_required":10000,		// minimum combat experience required
													// to learn this skill.
							"jing_cost":30,
						   "difficulty":30, // the base int to learn this skill
											// modify is gin_cost's (difficulty - int)*5%
							"max_skill":30, // the maximum level you can learn
							"min_skill":0   // the maximum level you can learn
											// from this object.
		]));
	}
}
