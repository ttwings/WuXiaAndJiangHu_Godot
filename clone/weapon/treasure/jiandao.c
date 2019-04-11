// jiandao.c 五毒剪
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit HOOK;

void create()
{
	set_name("五毒剪", ({ "wudu jian", "jian" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄奇门兵器，好似一只大剪刀，上面喂了剧毒。\n");
		set("value", 10000);
		set("material", "steel");
		set("wield_msg", "$N「唰」的一声掏出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n挂在腰间。\n");
	}
	init_hook(130);
	setup();
}
