// tangshi_book.c

inherit ITEM;

void create()
{
	set_name("唐诗剑谱", ({"tangshi jianpu", "book"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long","这是一本唐诗选辑。经过水浸泡后一些字显得格外醒目：

    “江陵城南偏西天宁寺大殿佛像向之虔诚膜拜通灵祝告如来赐福往生极乐”。

\n");
		set("value", 1500);
		set("material", "paper");
		set("skill", ([
			"name":	 "tangshi-jian",      //name of the skill
			"exp_required": 1 ,	   //minimum combat experience required
			"jing_cost":    10+random(10),// jing cost every time study this
			"difficulty":	10,	   // the base int to learn this skill
			"min_skill":	0,	    // the minimum level you can learn
			"max_skill":	49	    // the maximum level you can learn
		]) );
	}
}
