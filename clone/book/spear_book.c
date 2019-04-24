// spear_book.c

inherit ITEM;

void create()
{
	set_name("岳家枪法", ({"paper", "shu", "book"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本岳家枪法残本，是岳武穆送给上官帮主的。可惜年深月久，书以有些残破了。\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
								 "name":"spear", // name of the skill
						 "exp_required":1000,	// minimum combat experience required
							"jing_cost":20,		 // jing cost every time study this
						   "difficulty":20,		 // the base int to learn this skill
							"max_skill":99,		 // the maximum level you can learn
							"min_skill":30,		 // the minimum level you can learn
		]));
	}
}
