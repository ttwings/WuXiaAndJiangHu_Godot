// seng-cloth.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

string *clothname = ({
	CYN "灰布袈裟" NOR,
	HIB "青布袈裟" NOR,
	YEL "粗布袈裟" NOR,
	CYN "灰布直裰" NOR,
	HIB "青布直裰" NOR,
	YEL "粗布直裰" NOR,
});
string *clothid = ({
	"jia sha",
	"jia sha",
	"jia sha",
	"zhi duo",
	"zhi duo",
	"zhi duo",
});
string *clothlong = ({
	"这是一件出家人常穿的灰布袈裟。\n",
	"这是一件出家人常穿的青布袈裟。\n",
	"这是一件出家人常穿的粗布袈裟。\n",
	"这是一件出家人随常所穿的灰布直裰。\n",
	"这是一件出家人随常所穿的青布直裰。\n",
	"这是一件出家人随常所穿的粗布直裰。\n",
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
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 3);
	}
	setup();
}
