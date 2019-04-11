// seng-shoe.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

string* shoename = ({
	HIB "青布僧鞋" NOR,
	CYN "灰布僧鞋" NOR,
	HIY "麻布僧鞋" NOR,
});
string* shoeid = ({
	"seng xie",
	"seng xie",
	"seng xie",
});
string* shoelong = ({
	"这是一双出家人用的青布僧鞋。\n",
	"这是一双出家人用的灰布僧鞋。\n",
	"这是一双出家人用的麻布僧鞋。\n",
});

void create()
{
	int i = random(sizeof(shoename));

	set_name(shoename[i], ({ shoeid[i], "shoe" }));
	set_weight(900);
        set("long", shoelong[i]);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "双");
        //	set("long", shoelong[i]);
		set("value", 0);
		set("armor_prop/armor", 1 );
	}
	setup();
}
