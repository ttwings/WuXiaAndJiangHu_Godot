// dao-shoe.c
// Last Modified by winder on May. 25 2001

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

string* shoename = ({
	"灰布鞋",
	HIC"青布鞋"NOR,
	HIY"麻鞋"NOR,
	YEL"草鞋"NOR,
});
string* shoeid = ({
	"bu xie",
	"bu xie",
	"ma xie",
	"cao xie",
});
string* shoelong = ({
	"这是一双发白的灰布鞋。\n",
	"这是一双道家修行的青布鞋。\n",
	"这是一双出家修行人常穿的麻鞋。\n",
	"这是一双出家修行人的草鞋。\n",
});

void create()
{
	int i = random(sizeof(shoename));

	set_name(shoename[i], ({ shoeid[i], "shoe" }));
	set_weight(1000);
        set("long", shoelong[i]);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
//		set("long", shoelong[i]);
        	set("value", 0);
		set("material", "boots");
		set("armor_prop/dodge", 5);
	}
	setup();
}
