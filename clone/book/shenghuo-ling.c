// shenghuo-ling 圣火令

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name("圣火令", ({"shenghuo ling", "shenghuo", "ling"}));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "把");
		set("value", 10000);
		set("material", "steel");
		set("no_drop", "1");
		set("long", "这是一柄两尺来长的黑牌，非金非铁。质地坚硬无比，\n"
					"似透明，令中隐隐似有火焰飞腾，实则是令质映光，颜\n"
					"色变幻。令上刻得有不少波斯文字。 \n");
		set("wield_msg", HIY "$N“唰”的一声，从腰间抽出一片黑黝的铁牌握在手中。\n");
		set("unwield_msg", HIY "$N将圣火令插回腰间。\n" NOR);
	}
	set("skill", ([
							 "name":"shenghuo-ling",
					 "exp_required":50000,
						"jing_cost":40,
					   "difficulty":30,
						"max_skill":200,
						"min_skill":100]));
	init_sword(50);
	setup();
}
