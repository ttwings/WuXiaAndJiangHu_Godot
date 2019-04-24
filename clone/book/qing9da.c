// qing9da.c

inherit ITEM;

void create()
{
	set_name("青字九打", ({"qingzi9da", "book1"}));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本很古旧的线装书，青字九打是青城镇山绝技。\n");
		set("value", 7000);
		set("material", "paper");
		set("skill", ([
								 "name":"qingzi9da", // name of the skill
						 "exp_required":10000,		 // minimum combat experience required
							"jing_cost":40,			 // jing cost every time study this
						   "difficulty":20,			 // the base int to learn this skill
							"max_skill":150,		 // the maximum level you can learn
							"min_skill":100			 // the maximum level you can learn
		]));
	}
}
