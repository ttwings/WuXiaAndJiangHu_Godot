// cheng18po.c

inherit ITEM;

void create()
{
	set_name("城字十八破", ({ "cheng18po", "book2" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本发黄的手抄典籍。\n");
		set("value", 4000);
		set("material", "paper");
		set("skill", ([
			"name":	      "chengzi18po",	// name of the skill
			"exp_required":	10000,	// minimum combat experience required
			"jing_cost":	30,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100,// the maximum level you can learn
			"min_skill":	50	// the maximum level you can learn
		]) );
	}
}

