// bt_book1.c 药理经
// Last Modified by Winder on May. 15 2001

inherit ITEM;

void create()
{
	set_name("药理经", ({"yaoli jing", "jing", "yaoli"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本讲述药理的书。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
								 "name":"xidu-poison", // name of the skill
						 "exp_required":500,		   // minimum experience required
							"jing_cost":15,			   // jing cost every time study this
						   "difficulty":18,			   // the base int to learn this skill
							"max_skill":31			   // the maximum level you can learn
		]));
	}
}
