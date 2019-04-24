// ni-shoe.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

string *shoename = ({
	HIC "青布尼鞋" NOR,
	HIC "灰布尼鞋" NOR,
});
string *shoeid = ({
	"ni xie",
	"ni xie",
});
string *shoelong = ({
	"这是一双出家女尼常穿的青布鞋。\n",
	"这是一双出家女尼常穿的灰布鞋。\n",
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
		//	set("long", shoelong[i]);
		set("value", 0);
		set("armor_prop/armor", 1);
		set("female_only", 1);
	}
	setup();
}
