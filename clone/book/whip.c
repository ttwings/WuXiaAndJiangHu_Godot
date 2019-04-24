// whip.c

inherit ITEM;

void create()
{
	set_name("鞭法总诀", ({"shu", "book"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "册");
		set("long", "这是一册修习鞭法的武经\n里面记载着全真派掌教丹阳子多年的练功心得，画册中人物姿势如玉龙盘柱、如金凤飞舞。\n");
		set("value", 500);
		set("material", "book");
		set("skill", ([
								 "name":"whip", // name of the skill
						 "exp_required":0,		// minimum combat experience required
							"jing_cost":15,		// jing cost every time study this
						   "difficulty":20,		// the base int to learn this skill
							"max_skill":100		// the maximum level you can learn
		]));
	}
}
