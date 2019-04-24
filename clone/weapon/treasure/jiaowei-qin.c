//jiaowei qin 焦尾琴

#include <weapon.h>
#include <ansi.h>

inherit F_UNIQUE;
inherit SWORD;

void create()
{
	set_name(HIM "焦尾琴" NOR, ({"jiaowei qin", "qin"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "张");
		set("value", 40000);
		set("material", "steel");
		set("long", "相传这便是当年蔡文姬从火中所救出的焦木做成的美琴，琴的尾端仍可见焦黑色。\n");
		set("wield_msg", HIY "$N伸手轻轻一挥,一张焦尾琴便已出现在$N手中.\n" NOR);
		set("unwield_msg", HIY "$N十指一拂，琴声曳然而止。$N收起焦尾琴，放进背着的包袱里。\n" NOR);
		//		set("unequip_msg",HIY"你十指一拂，琴声曳然而止。你收起焦尾琴，放进背着的包袱里。.\n"NOR);
	}
	init_sword(150);
	setup();
}

//int wield()
//{
//	object ob = environment();

/*	if (ob && !wizardp(ob)) {
		tell_object(ob, name() + "是巫师用品，你不能使用，请马上向巫师报告，否则后果自负。\n");
		call_out("let_him_die", 300, ob);
		return 0;
	}*/
//	return ::wield();
//}
/*
void let_him_die(object ob)
{
	if (ob = environment()) {
		ob->add("combat_exp", -30000);
		ob->set_temp("last_damage_from", "盗用巫师用品中毒");
		ob->die();
	}
}
*/
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
	int n;

	if (me->query_skill_mapped("sword") != "liangyi-sword" ||
			me->query_skill("liangyi-sword", 1) < 100)
		//                return damage_bonus / 2;
		return 0;

	switch (random(4))
	{
	case 0:
		if (!victim->is_busy())
		{
			victim->start_busy(me->query_skill("sword") / 100 + 1);
			return WHT "$N" WHT "一声断喝，单手猛然拂过手中焦尾琴，焦尾琴顿时发出一股尖锐的"
								 "琴音，$n" WHT "只觉头晕目眩，几欲昏厥！\n" NOR;
		}
	case 1:
		n = me->query_skill("sword");
		victim->receive_damage("qi", n * 3 / 4, me);
		victim->receive_wound("qi", n * 3 / 4, me);
		return WHT "$N" WHT "一声冷哼，手中焦尾琴一振，霎时龙吟骤起，一道剑气携着尖"
							 "锐的琴音直射$n" WHT "而去！\n" NOR;
	}
	return damage_bonus;
}