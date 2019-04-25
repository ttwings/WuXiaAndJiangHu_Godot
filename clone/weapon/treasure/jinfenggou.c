// jinfenggou.c 金凤钩
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit HOOK;
inherit F_UNIQUE;

void create()
{
	set_name(HIY "金凤钩" NOR, ({"jinfeng gou", "gou"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("long", "这是一柄喂了剧毒的金钩，钩端好似一只蛇头。\n");
		set("value", 10000);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n插回鞘中。\n");
	}
	init_hook(130);
	setup();
}
