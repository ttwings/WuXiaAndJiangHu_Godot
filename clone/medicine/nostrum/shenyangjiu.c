// shenyangjiu.c 参阳玉酒
// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

void init()
{
	if (!wizardp(this_player()))
	{
		set("no_give", "这么珍贵的酒，哪能随便给人？\n");
		set("no_drop", "这么宝贵的美酒，扔了多可惜呀！\n");
		set("no_sell", "这样的美酒都要卖,你太不解风情了吧。\n");
	}
	add_action("do_drink", "drink");
	add_action("do_drink", "he");
}

void create()
{
	set_name(YEL "参阳玉酒" NOR, ({"shenyang yujiu", "jiu"}));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "壶");
		set("long", "一壶金黄的粘稠药酒，是凌霄城的珍藏，饮之于学武大有裨益。\n");
		set("value", 0);
		set("drug_type", "补品");
	}
	set("is_monitored", 1);
	set("pour_type", "1");
	setup();
}

int do_drink(string arg)
{
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要喝什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要喝什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢喝，小心别呛着了。\n");

	if (me->query("eff_jing") >= me->query("max_jing") &&
		me->query("eff_qi") >= me->query("max_qi"))
	{
		write("你满面红光的，喝如此凶的酒不怕上火？\n");
		return 1;
	}
	me->set("eff_jing", (int)me->query("max_jing"));
	me->set("jing", (int)me->query("max_jing"));
	me->set("eff_qi", (int)me->query("max_qi"));
	me->set("qi", (int)me->query("max_qi"));
	me->set("neili", (int)me->query("max_neili"));
	message_vision(HIW "$N举杯饮下参阳玉酒，只觉小腹间热气上冲，跟着胸口间便\n如火烧般热了起来，只觉通体融和，四骸俱泰。\n" NOR, me);
	destruct(this_object());
	return 1;
}
