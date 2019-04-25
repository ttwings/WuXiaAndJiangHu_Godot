// yujie.c

#include <ansi.h>
#include <armor.h>

inherit FINGER;

void create()
{
	set_name(CYN "玉戒指" NOR, ({"yu jiezhi", "jiezhi", "finger"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "白玉雕成的戒指，莹白圆润\n");
		set("unit", "枚");
		set("value", 30000);
		set("material", "jade");
		set("armor_prop/armor", 3);
	}
	setup();
}
