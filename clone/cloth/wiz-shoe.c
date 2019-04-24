// wiz-shoe.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

string *shoename = ({
	HIB "天师靴" NOR,
	HIG "步云履" NOR,
	HIY "众神之车" NOR,
});
string *shoeid = ({
	"wizard shoe",
	"cloth shoes",
	"skin shoes",
});
string *shoelong = ({
	"这是一双巫师随常使用的皮靴。\n",
	"这是一双用上好龙皮作的皮靴。\n",
	"这是一双白玉镶就的飞腾之靴。\n",
});

void create()
{
	int i = random(sizeof(shoename));

	set_name(shoename[i], ({shoeid[i], "shoe"}));
	set_weight(900);
	set("long", shoelong[i]);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("material", "cloth");
		set("unit", "双");
		// 	set("long", shoelong[i]);
		set("value", 0);
		set("armor_prop/armor", 100);
	}
	setup();
}
