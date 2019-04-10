// force.c

inherit SKILL;

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int damage;

	me->add("neili", - factor );
	damage = (int)me->query("neili")/20 + factor
		- (int)victim->query("neili")/25;

	if( damage < 0 ) {
		if( !me->query_temp("weapon")
		&&	random(victim->query_skill("force")) > me->query_skill("force")/2 ) {
			damage = - damage;
			me->receive_damage( "qi", damage * 2 );
			me->receive_wound( "qi", damage );
			if( damage < 10 ) return "$N受到$n的内力反震，闷哼一声。\n";
			else if( damage < 20 ) return "$N被$n以内力反震，「嘿」地一声退了两步。\n";
			else if( damage < 40 ) return "$N被$N以内力一震，胸口有如受到一记重锤，连退了五六步！\n";
			else return "$N被$n的内力一震，眼前一黑，身子向后飞出丈许！！\n";
		}
		if( damage_bonus + damage < 0 ) return - damage_bonus;
		return damage;
	}

	damage -= victim->query_temp("apply/armor_vs_force");
	if( damage_bonus + damage < 0 ) return - damage_bonus;
	if( random(me->query_skill("force")) < damage )
		return damage;
}

//mixed be_hit_ob(object me, object victim, int damage_bonus, int factor) 
// 可以重载,被打中的效果,factor 为对方的加力,damage_bonus 是对方的
//臂力值,是计算最后伤害的基数之一.
