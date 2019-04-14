// weapond.c

#include <ansi.h>
#include <combat.h>

mapping weapon_actions = ([
	"slash": ([
		"damage_type":  "割伤",
		"action":       "$N挥动$w，斩向$n的$l",
		"parry":        20,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"slice": ([
		"damage_type":  "劈伤",
		"action":       "$N用$w往$n的$l砍去",
		"dodge":        20,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"chop": ([
		"damage_type":  "劈伤",
		"action":       "$N的$w朝著$n的$l劈将过去",
		"parry":        -20,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"hack": ([
		"action":       "$N挥舞$w，对准$n的$l一阵乱砍",
		"damage_type":  "劈伤",
		"damage":       30,
		"dodge":       	30,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"thrust": ([
		"damage_type":  "刺伤",
		"action":       "$N用$w往$n的$l刺去",
		"dodge":        15,
		"parry":        -15,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"pierce": ([
		"action":       "$N的$w往$n的$l狠狠地一捅",
		"damage_type":  "刺伤",
		"dodge":        -30,
		"parry":        -30,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"whip": ([
		"action":       "$N将$w一扬，往$n的$l抽去",
		"damage_type":  "鞭伤",
		"dodge":        -20,
		"parry":        30,
	]),
	"impale": ([
		"action":       "$N用$w往$n的$l直戳过去",
		"damage_type":  "刺伤",
		"dodge":        -10,
		"parry":        -10,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"strike": ([
		"action":       "$N一个大舒臂抡起$w，对着$n的$l往下一砸",
		"damage_type":  "筑伤",
		"dodge":        -10,
		"parry":        -10,
		"post_action":  (: call_other, __FILE__, "slash_weapon" :),
	]),
	"bash": ([
		"action":       "$N挥舞$w，往$n的$l用力一砸",
		"damage_type":  "挫伤",
		"post_action":  (: call_other, __FILE__, "bash_weapon" :),
	]),
	"crush": ([
		"action":       "$N高高举起$w，往$n的$l当头砸下",
		"damage_type":  "挫伤",
		"post_action":  (: call_other, __FILE__, "bash_weapon" :),
	]),
	"slam": ([
		"action":       "$N手握$w，眼露凶光，猛地对准$n的$l挥了过去",
		"damage_type":  "挫伤",
		"post_action":  (: call_other, __FILE__, "bash_weapon" :),
	]),
	"throw": ([
		"action":       "$N将$w对准$n的$l射了过去",
		"damage_type":  "刺伤",
		"post_action":  (: call_other, __FILE__, "throw_weapon" :),
	]),
]);

varargs mapping query_action()
{
	string verb, *verbs;

	verbs = previous_object()->query("verbs");

	if( !pointerp(verbs) ) return weapon_actions["hit"];
	else {
		verb = verbs[random(sizeof(verbs))];
		if( !undefinedp(weapon_actions[verb]) )
			return weapon_actions[verb];
		else return weapon_actions["hit"];
	}	
}

void throw_weapon(object me, object victim, object weapon, int damage)
{
	if( objectp(weapon) )
	{
		if( (int)weapon->query_amount()==1 )
		{
			weapon->unequip();
			tell_object(me, "\n你的" + weapon->query("name") + "用完了！\n\n");
		}
		weapon->add_amount(-1);
	}
}

void bash_weapon(object me, object victim, object weapon, int damage)
{
	object ob;
	int wap, wdp;

	if( objectp(weapon) && damage==RESULT_PARRY &&
		ob = victim->query_temp("weapon") )
	{
		wap = (int)weapon->weight() / 500
			+ (int)weapon->query("rigidity")
			+ (int)me->query("str");
		wdp = (int)ob->weight() / 500
			+ (int)ob->query("rigidity")
			+ (int)victim->query("str");
		wap = random(wap);

		if( wap > 5 * wdp)
		{
			message_vision(HIM"只听见「啪」地一声，$N手中的"+ob->name()+HIM"已经断为两截！\n"NOR,victim);
			ob->unequip();
			ob->move(environment(victim));
			ob->set("name","断掉的"+ob->query("name"));
			ob->set("value", 49);
			ob->set("weapon_prop", 0);
			victim->reset_action();
		} 
		else if( wap > 3 * wdp )
			{
				message_vision(HIY"$N只觉得手中"+ob->name()+HIY"把持不定，脱手飞出！\n"NOR,victim);
				ob->unequip();
				ob->move(environment(victim));
				victim->reset_action();
			} 
			else if( wap > wdp )
				{
					message_vision(HIW "$N只觉得手中" + ob->name() + HIW"一震，险些脱手！\n"NOR, victim);
				}
				else
				{
					message_vision(HIR"$N的"+weapon->name()+HIR"和$n的"+ob->name()+HIR"相击，冒出点点的火星。\n"NOR,me,victim);
				}
	}
}

void slash_weapon(object me, object victim, object weapon, int damage)
{
	object weapon1;        
	string poison;
	int poison1, wp, wp1, wp2;  
	weapon1=victim->query_temp("weapon");

	if(objectp(weapon) && objectp(weapon1))
	{
		wp = weapon->query("weapon_prop/damage");
		wp1 = weapon1->query("weapon_prop/damage");
		wp2 = weapon1->query("rigidity");
		if(wp > 1000) wp = 1000;
		if(wp1 > 1000) wp1 = 1000;
		if(wp2 > 100) wp2 = 100;
		if( wp > 0 && wp > (wp1 + wp2) * 5 &&
			random(me->query("str")) > victim->query("str")/2)
		{
			message_vision(WHT "只听见「哐」地一声轻响，$N手中的"+weapon1->name()+WHT"已经被"+weapon->name()+WHT"削为两截！\n"NOR, victim );
			weapon1->unequip();
			weapon1->move(environment(victim));
			weapon1->set("name", "断掉的"+weapon1->query("name"));
			weapon1->set("value", 49);
			weapon1->set("weapon_prop", 0);
			victim->reset_action();
		} 
	}

	if (stringp(poison=weapon->query("poisoned")) && 
		((int)victim->query("eff_qi") < (int)victim->query("max_qi"))) 
		if(intp(poison1=weapon->query("poison_number")) && random(10)> 5
			&& poison1 > 1 && victim->query_condition(poison) < 50)
		{
			if (poison1 == 2)                   
				weapon->set_temp("apply/long", ({weapon->query("long")+"好象是被喂过剧毒，不过效果已经不明显了。\n"}));
				weapon->add("poison_number", -1);
				victim->apply_condition(poison, victim->query_condition(poison) + random(10));
				message_vision(HIR"$n只觉得伤口上一麻，大叫一声：不好！\n"NOR,me,victim);
				if(!victim->is_killing(me->query("id"))) victim->kill_ob(me);
		}
}

