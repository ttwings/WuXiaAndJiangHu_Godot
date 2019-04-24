// manao.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "Âêè§" NOR, ({"ma nao", "manao"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "Ò»¿é¾§Ó¨¹ÅÑÅµÄÂêè§¡£\n");
		set("unit", "¿é");
		set("value", 70000);
	}
}
