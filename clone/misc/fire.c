// /clone/misc/fire.c
// Last Modified by Winder on May. 15 2001

inherit ITEM;

void create()
{
	set_name("火折", ({"fire", "huozhe"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "这是一支用于引火的火折，到了黑暗的地方就用(use)得着了。\n");
		set("unit", "支");
		set("value", 100);
	}
}
