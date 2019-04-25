// basic_hand_book.c

inherit ITEM;

void create()
{
	set_name("手法精要", ({"shoufa pu", "pu"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是两张纸片，上面密密麻麻的写着练功的口诀要旨。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
								 "name":"hand", // name of the skill
						 "exp_required":0,		// minimum combat experience required
							"jing_cost":20,		// jing cost every time study this
						   "difficulty":20,		// the base int to learn this skill
							"max_skill":101		// the maximum level you can learn
		]));
	}
}
