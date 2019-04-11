// tianchang-zhangpu.c 天长掌法谱
// By sir 5/20/2001

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name(HIW"天长掌法谱" NOR, ({ "tianchang zhangpu","zhangpu", }));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	     set("unit", "本");
	     set("long",
	"这是一本很破旧的小册，上面好象还有一些小人挥舞拳脚的图形。\n",
	 );
	 set("value", 0);
	 set("material", "paper");
	 set("skill", ([
			"name":       "tianchang-zhang",
			"exp_required" : 10000,
			"jing_cost":  30,
			"difficulty": 20,
			"max_skill":  80
		]) );
	}
}
