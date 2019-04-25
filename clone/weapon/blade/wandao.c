// wandao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit BLADE;

string *names = ({
	"长弯刀",
	"短弯刀",
	"月牙弯刀",
});

string *ids = ({
	"chang wan dao",
	"duan wan dao",
	"yueya wan dao",
});

void create()
{
	int i = random(sizeof(names));
	set_name(names[i], ({ids[i], "wan dao", "blade"}));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一把弯弯的战刀．\n");
		set("unit", "把");
		set("value", 400);
		set("material", "metal");
	}
	init_blade(25);
	setup();
}
