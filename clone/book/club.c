//club.c

inherit ITEM;

void create()
{
	set_name("棍法通解", ({"shu", "book"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本修习棍法的武经。\n里面记载着少林派弟子数百年的练功心得，上面画着各式舞棍的小人。\n");
		set("value", 500);
		set("material", "book");
		set("skill", ([
								 "name":"club", // name of the skill
						 "exp_required":0,		// minimum combat experience required
							"jing_cost":20,		// jing cost every time study this
						   "difficulty":20,		// the base int to learn this skill
							"max_skill":100		// the maximum level you can learn
		]));
	}
}
