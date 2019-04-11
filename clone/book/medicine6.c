// medicine6.c
// Last Modified by Winder on May. 29 2001

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name(HIC"胡青牛医经"NOR, ({ "huqingniu yijing", "yijing", "jing"}));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long","这是蝶谷医仙胡青牛一生心血汇集成的医书。\n");
		set("value", 1500);
		set("material", "paper");
		set("skill", ([
			"name":         "medicine",
			"exp_required": 100 ,
			"jing_cost":    30+random(10),
			"difficulty":   20,
			"min_skill":    100,
			"max_skill":    200
		]) );
	}
}
