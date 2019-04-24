// zhenzhu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(WHT "ÕäÖé" NOR, ({"zhen zhu", "zhu"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "Ò»Á£ÁúÑÛ´óµÄÕäÖé¡£\n");
		set("unit", "Á£");
		set("value", 20000);
	}
}
