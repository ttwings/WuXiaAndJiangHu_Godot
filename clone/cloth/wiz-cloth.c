// wiz-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

string *clothname = ({
	HIB "天师袍" NOR,
	HIC "无缝天衣" NOR,
	HIY "黄金战甲" NOR,
});
string *clothid = ({
	"wizard cloth",
	"wizard cloth",
	"wizard cloth",
});
string *clothlong = ({
	"这是一件巫师随常穿的休闲衣服。\n",
	"这是一件织女银梭织就的无缝天衣。\n",
	"这是一件黄金打造的无敌战甲。\n",
});

void create()
{
	int i = random(sizeof(clothname));

	set_name(clothname[i], ({clothid[i], "cloth"}));
	set_weight(1000);
	set("long", clothlong[i]);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		//	set("long", clothlong[i]);
		set("unit", "件");
		set("value", 0);
		set("material", "cloth");
		set("armor_prop/armor", 100);
		set("armor_prop/personality", 300);
	}
	setup();
}
