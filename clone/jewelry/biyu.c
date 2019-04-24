// biyu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIG "±ÌÓñ" NOR, ({"bi yu", "yu"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "Ò»¿é±ÌÂÌÈç¶ĞµÄÓñ¡£\n");
		set("unit", "¿é");
		set("value", 80000);
	}
}
