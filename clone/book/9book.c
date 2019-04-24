// 9book.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
	set_name(HIY "《九阴真经》" NOR, ({"jiuyin zhenjing", "9jing", "jing"}));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是黄裳手书的《九阴真经》。纸张虽然已经发黄，但笔势依然可以看出飞洒如云烟：\n天之道，损有余而补不足，是故虚胜实，不足胜有余。\n");
		set("value", 3000);
		set("no_get", 1);
		set("no_put", 1);
		set("no_drop", 1);
		set("material", "paper");
	}
}
void init()
{
	if (!query("inited"))
	{
		set("inited", 1);
		remove_call_out("destbook");
		call_out("destbook", random(1200) + 50);
	}
}
void destbook()
{
	message_vision(HIY "迎面走来一个模样猥琐的中年男人，与你擦身而过。你心中突然一个念头冒起来：“我的$N！”\n" HIC "转身欲追，中年男人已经消失不见了。\n" NOR, this_object());
	destruct(this_object());
}

void owner_is_killed()
{
	destruct(this_object());
}
