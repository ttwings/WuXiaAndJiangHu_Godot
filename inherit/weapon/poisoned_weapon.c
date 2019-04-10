// Last Modified by winder on Feb. 28 2001
// Poisoned weapon
// set("poisoned", "poison-name");

#include <ansi.h>
#include <combat.h>

mixed hit_ob(object me, object victim, int damage)
{
	object weapon, weapon1;	
	string poison;
	int poison1, wp, wp1, wp2, wap, wdp;
	object piece;
	weapon=this_object();
	weapon1=victim->query_temp("weapon");

	if(objectp(weapon) && objectp(weapon1) && weapon->query("flag") == 4)
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
			message_vision(HIM"只听见「哐」地一声轻响，$N手中的"+weapon1->name()+HIY"已经被"+weapon->name()+HIY"削为两截！\n"NOR,victim);
			weapon1->unequip();
			victim->reset_action();
     	seteuid(getuid());
     	piece = new("/clone/misc/piece");
     	piece->set("long", "断成两截的"+weapon1->query("name")+"。\n");
     	piece->set_name( "断掉的"+weapon1->query("name"), ({weapon1->query("id"),"piece"}) );
     	piece->move(environment(victim));
    	destruct(weapon1);
		} 
	}
	else
		if( objectp(weapon) && objectp(weapon1) && 
			weapon1->query("material") != "softsteel" &&
			weapon1->query("skill_type") != "whip" &&
			weapon1->query("rigidity") < weapon->query("rigidity") &&
			!weapon1->query("rao") ) //绕指柔剑
		{
			wap = (int)weapon->weight() / 500 +
				(int)weapon->query("rigidity") +
				(int)me->query("str");
			if(weapon->query_amount() > 1)
				wap = ((int)weapon->query("base_weight") *
					weapon->query_amount() / 500) +
					(int)weapon->query("rigidity") +
					(int)me->query("str");
			wdp = (int)weapon1->weight() / 500 +
				(int)weapon1->query("rigidity") +
				(int)victim->query("str");
			if(weapon1->query_amount() > 1)
				wap = ((int)weapon1->query("base_weight") *
					weapon1->query_amount() / 500) +
					(int)weapon1->query("rigidity") +
					(int)victim->query("str");
			wap = random(wap);
			if( wap > 5 * wdp)
			{
				message_vision(HIM"只听见「啪」地一声，$N手中的"+weapon1->name()+HIM"已经断为两截！\n"NOR,victim);
				weapon1->unequip();
				victim->reset_action();
       	seteuid(getuid());
       	piece = new("/clone/misc/piece");
      	piece->set("long", "断成两截的"+weapon1->query("name")+"。\n");
      	piece->set_name( "断掉的"+weapon1->query("name"), ({weapon1->query("id"),"piece"}) );
     	  piece->move(environment(victim));
      	destruct(weapon1);
			} 
			else if( wap > 3 * wdp )
				{
					message_vision(HIY"$N只觉得手中"+weapon1->name()+HIY"把持不定，脱手飞出！\n"NOR,victim);
					weapon1->unequip();
					weapon1->move(environment(victim));
					victim->reset_action();
				} 
				else if( wap > wdp )
					{
						message_vision(HIW "$N只觉得手中" + weapon1->name() + HIW"一震，险些脱手！\n"NOR, victim);
					}
					else
					{
						message_vision(HIR"$N的"+weapon->name()+HIR"和$n的"+weapon1->name()+HIR"相击，冒出点点的火星。\n"NOR,me,victim);
					}
		}

	if (stringp(poison=weapon->query("poisoned")) && 
		((int)victim->query("eff_qi") < (int)victim->query("max_qi"))) 
		if(intp(poison1=weapon->query("poison_number")) &&
			random(10) > 5 && poison1 > 1 &&
			victim->query_condition(poison) < 50)
		{
			if (poison1 == 2)
				weapon->set_temp("apply/long", ({weapon->query("long")+"好象是被喂过剧毒，不过效果已经不明显了。\n"}));
			weapon->add("poison_number", -1);
			victim->apply_condition(poison, victim->query_condition(poison) + random(10));
			if(victim->query("race") == "人类" && !victim->query("mute"))
				message_vision(HIR "$N只觉得伤口上一麻，大叫一声：不好！\n"NOR,victim);
			else if(victim->query("race") == "人类")
				message_vision(HIR "$N只觉得伤口上一麻，眉头一挤，显然是发怒了！\n"NOR,victim);
				else message_vision(HIR"$N猛然一颤，伤口处流出黑血，凶相毕露！\n"NOR,victim);
			if(!victim->is_killing(me->query("id"))) victim->kill_ob(me);
		}
	return this_object()->weapon_hit_ob(me, victim, damage);
}

