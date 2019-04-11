// zixia_book.c  紫霞秘芨
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(MAG"紫霞密芨"NOR, ({ "zixia_book", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
//		set("no_drop",1);
		set("long",
HIM"天下武功，以练气为正。浩然正气，原为天授，惟常人不善
养之，反以性伐气。武夫之患，在性暴、性骄、性酷、性贼。
暴则神扰而气乱，骄则真离而气浮，酷则丧仁而气失，贼则
心狠而气促。此四事者，皆是截气之刀锯。舍尔四性，返诸
柔善，制汝暴酷，养汝正气，鸣天鼓，饮玉浆，荡华池，叩
金梁，据而行之，当有小成。\n"NOR);
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	 "zixia-shengong",	// name of the skill
			"exp_required": 50000,		// minimum combat experience required
								// to learn this skill.
			"jing_cost" :   30,
			"difficulty":   30,			// the base int to learn this skill
								// modify is gin_cost's (difficulty - int)*5%
			"max_skill":    99,			// the maximum level you can learn
			"min_skill":    0			// the maximum level you can learn
								// from this object.
		]) );
	}
}
int query_autoload() { return 1; }

