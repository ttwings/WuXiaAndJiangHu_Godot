// Last Modified by winder on May. 29 2001

inherit ITEM;

void create()
{
	set_name("武僧棍法", ({"clubbook", "shu", "book"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "此书相传为唐初少林十三棍僧所著\n是一本薄卷，上面有一些人形持棍棒战斗的画页，下面写了许多口诀。\n");
		set("treasure", 1);
		set("value", 200);
		set("material", "paper");
		set("skill", ([
								 "name":"club", // name of the skill
						 "exp_required":1000,   // minimum combat experience
												// required
							"jing_cost":25,		//jing cost every time study this
						   "difficulty":20,		// the base int to learn this skill
							"max_skill":100		// the maximum level you can learn
		]));
	}
}
