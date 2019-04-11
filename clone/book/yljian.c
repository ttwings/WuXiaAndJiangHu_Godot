// yljian.c

inherit ITEM;

void create()
{
set_name( "云龙剑谱",({ "jian book","book"}));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","这是一本剑谱总诀。\n");
		set("value", 5000);
		set("material", "paper");
		set("skill", ([
			"name": "yunlong-jian",  //name of the skill
			"exp_required": 10000 , //minimum combat experience required
			"jing_cost": 20+random(30),// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	119,	// the maximum level you can learn
			"min_skill":	80	// the minimum level you can learn
		]) );
	}
}
