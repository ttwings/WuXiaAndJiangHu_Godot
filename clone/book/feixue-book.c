// feixue-book.c
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIC"飞雪掌谱"NOR, ({ "feixue-book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本学飞雪映梅掌的书。\n");
		set("value", 1000);
		set("material", "paper");
		set("skill", ([
			"name":	 "snow-strike",
			"exp_required": 10000,
			"jing_cost" :   20,
			"difficulty":   20,
			"max_skill":    80,
			"min_skill":    20
		]) );
	}
}

