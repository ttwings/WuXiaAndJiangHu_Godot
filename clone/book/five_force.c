// book1.c

inherit ITEM;

void create()
{
	set_name("五毒真经", ({ "jing", "book" }));
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本薄薄的小册，上面绘了许多打坐的人像。\n");
		set("value", 0);
		set("material", "paper");
		set("skill", ([
			"name": "wudu-shengong",	// name of the skill
			"exp_required": 0,      // minimum combat experience required
			"jing_cost":    20,     // jing cost every time study this
			"difficulty":   20,     // the base int to learn this skill
			"max_skill":    40      // the maximum level you can learn
		]) );
	}
}
