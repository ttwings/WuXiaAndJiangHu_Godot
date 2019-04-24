// yuwang-jian.c 越王勾践剑
// Edited by fandog, 02/15/2000
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name(HIY "越王" HIR "勾践" HIB "剑" NOR, ({"yuewang jian", "goujian jian", "jian", "sword"}));
	set_weight(20000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 30000);
		set("material", "iron");
		set("long", "这是越王勾践佩戴过的宝剑，寒光闪闪，冷气逼人。\n");
		set("wield_msg", "寒芒一闪，冷森森的$n已在$N手中。\n");
		set("unwield_msg", "$N手腕轻抖，$n倏忽间已然不见。\n");
	}
	init_sword(180);
	setup();
}
