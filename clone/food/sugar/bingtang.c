// bingtang.c

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(YEL "冰糖" NOR, ({"bing tang", "tang"}));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "冰糖。\n");
		set("unit", "块");
		set("value", 20); //很便宜，（基本食物都应该很便宜）.
		set("food_remaining", 3);
		set("food_supply", 10); //正常饭量的人一顿吃二斤。
	}
}
