// silverjian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
	set_name(HIW "银装锏" NOR, ({"silver mace", "mace", "silvermace", "yinjian", "jian"}));
	set_weight(8000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 8000);
		set("material", "silver");
		set("long", "一柄闪闪发光的银装锏，显然是被人擦了又擦。\n");
		set("wield_msg", "只见一道银光闪过，$N手里已经多了一柄$n！\n");
		set("unwield_msg", "$N收起了$n，四周光芒为之一暗！\n");
	}

	init_mace(65);
	setup();
}
