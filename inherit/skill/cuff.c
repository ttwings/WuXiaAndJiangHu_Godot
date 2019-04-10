inherit SKILL;

mixed hit_ob(object me, object victim, int damage_bonus)
{
   if (random(me->query_skill("cuff"))>150) { 
	victim->apply_condition("cuff_power", 1 +me->query_condition("cuff_power")+me->query("jiali"));
    }
}

//be_hit_ob(object me, object victim, int damage_bonus) 
//当被打中时调用受害者的parry上功夫的被打中效果,
//damage_bonus 是内力造成的总的伤害值,如果没有兵
//器就差不多是最后伤害值
 
