//lingshezhang.c
#include <weapon.h>
inherit STAFF;
inherit F_UNIQUE;

void create()
{
	set_name(HIR "灵蛇杖" NOR, ({"lingshe zhang", "zhang"}));
	set_weight(100000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "根");
		set("long", "这是一根蛇杖, 杖头一条小蛇, 红舌伸缩, 十分诡异。\n");
		set("value", 300);
		set("material", "leather");
		set("wield_msg", "$N「唰」的一声提起一根$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n收回背后。\n");
	}
	init_staff(150);
	setup();
}
