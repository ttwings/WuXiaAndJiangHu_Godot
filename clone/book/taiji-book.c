// taiji-book.c

inherit ITEM;

void create()
{
	set_name("太极拳经", ({ "taiji book", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", @LONG
这是一本发黄的手抄典籍。是张三丰亲手抄录的。翻开首页，每页都有招式图谱。

    o,     o,    o     o      o     o      o
    )-'   /|'    )-'   )-'   (-'    )-'    )-'
    >\     >\    >\   / >     >\   / >    / >


LONG);
		set("value", 8000);
		set("material", "paper");
		set("skill", ([
			"name":	  "taiji-quan",	// name of the skill
			"exp_required":	10000,	// minimum combat experience required
			"jing_cost":	30,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	30,// the maximum level you can learn
			"min_skill":	0	// the maximum level you can learn
		]) );
	}
}

