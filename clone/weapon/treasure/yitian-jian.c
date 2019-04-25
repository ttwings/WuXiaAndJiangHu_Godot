// yitianjian.c 倚天剑
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;

void create()
{
	set_name("倚天剑", ({"yitian jian", "sword", "jian"}));
	set_weight(15000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "柄");
		set("value", 50000);
		//		set("no_drop", "1");
		set("material", "iron");
		set("long", "这是天下第一利器，有“倚天不出，谁与争锋”之说。\n");
		set("wield_msg", "直如矫龙吞水，长虹冠日一般，$n已在$N手中，天地为之变色。\n");
		set("unwield_msg", "$N将$n插回腰间，华光顿敛，天地间只闻龙鸣。\n");
	}
	init_sword(170);
	enable_commands();
	setup();
}

int init()
{
	if (environment(this_object())->query("id") != "zhang wuji")
	{
		remove_call_out("destyitianjian");
		call_out("destyitianjian", 5400 + random(1800));
		return 1;
	}
	else
		return 0;
}

void destyitianjian()
{
	object ob;
	message_vision("突然有个黑衣人匆匆和你擦身而过，消失在街口拐角处，糟糕，你的$N丢了。\n", this_object());
	destruct(this_object());
	/*	message("channel:rumor", MAG"【谣言】某人："+"遗失多年的倚天剑又重现江湖啦。\n"NOR, users());*/
}
