// /clone/medicine/nostrum/binghuojiu.c 玄冰碧火酒
// Modified by Zeratul Jan 11 2001 force>特殊内功时喝酒增长内力，反之降内力

inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>

void init()
{
	add_action("do_drink", "drink");
	add_action("do_drink", "he");
}
void create()
{
	set_name(HIC "玄冰碧火酒" NOR, ({"xuanbingbihuo jiu", "jiu"}));
	set("unit", "壶");
	set("long", "这是一壶珍贵之极的玄冰碧火酒, 据说对内力修为有极大助益。\n");
	set("pour_type", "1");
	setup();
}
int do_drink(string arg)
{
	object me = this_player();
	mapping skill_map = me->query_skill_map();
	int force_limit = me->query_skill("force") * 10;
	int neili_limit = me->query("max_neili");

	if (!id(arg))
		return notify_fail("你要喝什么？\n");
	if (!present(this_object(), this_player()))
		return notify_fail("你要喝什么？\n");
	if (me->is_busy())
		return notify_fail("别急，慢慢喝，小心别呛着了。\n");

	if (arg == "jiu")
	{
		tell_object(me, HIM "你仰起头来，将壶中的酒尽数喝干，登时腹痛如绞。当下运起内力，\n要将肚中这团害人之物化去。哪知这酒的毒性非同小可，这一发作\n出来，只痛得你全身抽搐，手足痉挛，立时便欲晕去。\n" NOR);
		if (me->query_skill("force", 1) < me->query_skill(skill_map["force"], 1))
		{
			me->apply_condition("scorpion_poison", 20);
			me->apply_condition("snake_poison", 20);
			me->apply_condition("flower_poison", 20);
			me->add("max_neili", -random(50));
			tell_object(me, HIR "你抵挡不住猛烈的药性，登时晕死过去。\n" NOR);
			me->unconcious();
		}
		else if ((int)me->query_condition("binghuo") > 0)
		{
			tell_object(me, HIR "你才喝此酒未久，还没用内功化除净尽，新酒入口，实难抵挡。\n" NOR);
			me->add("max_neili", -random(20));
			me->unconcious();
		}
		else
		{
			tell_object(me, HIG "你将以前学过、见过的诸般武功施展出来，乱打乱拍。只觉每发出\n一拳一掌，腹中的疼痛便随内力的行走而带了一些出来。使了一阵\n拳脚，腹内疼痛也随之而减。直到剧毒尽数逼离肚腹，也就不再疼\n痛，内力修为似乎有了不小进益。\n" NOR);
			if (neili_limit < force_limit)
				me->add("max_neili", 30 + random(30));
		}
		me->apply_condition("binghuo", 500);
		destruct(this_object());
	}
	return 1;
}
