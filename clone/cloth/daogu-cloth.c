// daogu-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

string* clothname = ({
	HIM"花格道袍"NOR,
	HIY"麻格道袍"NOR,
	HIB"青布道袍"NOR,
	"灰布道袍"NOR,
});
string* clothid = ({
	"dao pao",
	"dao pao",
	"dao pao",
	"dao pao",
});
string* clothlong = ({
	"这是一件出家道姑常穿的花格道袍。\n",
	"这是一件出家道姑常穿的麻格道袍。\n",
	"这是一件出家道姑常穿的青布道袍。\n",
	"这是一件出家道姑常穿的灰布道袍。\n",
});

void create()
{
	int i = random(sizeof(clothname));

	set_name(clothname[i], ({ clothid[i], "cloth" }));
	set_weight(3000);
        set("long", clothlong[i]);      
        if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("value", 0);
//		set("long", clothlong[i]);
		set("material", "cloth");
		set("armor_prop/armor", 2);
		set("female_only", 1);
	}
	setup();
}
