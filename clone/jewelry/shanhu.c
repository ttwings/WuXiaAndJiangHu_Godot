// shanhu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR "珊瑚" NOR, ({"shan hu", "shanhu"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "一树如火般夺目光华的七尺珊瑚，很是珍贵。\n");
		set("unit", "树");
		set("value", 50000);
	}
}
