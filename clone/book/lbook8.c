// lbook8.c
#include <ansi.h>
inherit ITEM;
void create()
{
	set_name(YEL "「说文解字」" NOR, ({"literateb8", "shu8", "book8"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这本书封皮有点旧，上面写着「说文解字」几个字。\n");
		set("value", 10000);
		set("material", "paper");
		set("skill",
			([
						"name":"literate",
				"exp_required":0,
				   "jing_cost":20,
				  "difficulty":15,
				   "max_skill":29,
				   "min_skill":1,
		]));
	}
}
