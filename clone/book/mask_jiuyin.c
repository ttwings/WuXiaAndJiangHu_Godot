// /clone/book/mask_jiuyin.c 九阴假经

#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

int do_du(string arg);

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}

void create()
{
	set_name(YEL "九阴假经" NOR, ({"mask_jiuyin", "jiuyin-jiajing"}));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("material", "paper");
		set("no_drop", "你好不容易拿到手的宝经，你舍得丢么？\n");
		set("no_put", "这么宝贵的东西，不要到处乱放。\n");
		set("long", "这就是武林中人人梦寐以求的“九阴真经”啊，千万不要丢了哦。:P \n");
	}
}

int do_du(string arg)
{
	if (!arg && arg != "mask_jiuyin" && arg != "jiuyin-jiajing")
		return notify_fail("你要读什么？\n");
	if (!present(this_object(), this_player()))
		return 0;

	return notify_fail("没有人解释经义，你自己能看得懂么？\n");
}
