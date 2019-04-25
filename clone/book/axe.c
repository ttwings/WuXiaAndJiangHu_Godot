// axe.c

inherit ITEM;

void create()
{
	set_name("段家斧法", ({"shu", "book"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "册");
		set("long", "这是一册修行斧法的武经。\n"
					"里面记载着武学名家大理段氏的独门绝学段云斧的根基武功，\n"
					"画册中的小人一把开山大斧使得虎虎有声、威风八面。\n");
		set("value", 500);
		set("material", "book");
		set("skill", ([
								 "name":"axe", // name of the skill
						 "exp_required":0,	 // minimum combat experience required
							"jing_cost":15,	// jing cost every time study this
						   "difficulty":20,	// the base int to learn this skill
							"max_skill":100	// the maximum level you can learn
		]));
	}
}
