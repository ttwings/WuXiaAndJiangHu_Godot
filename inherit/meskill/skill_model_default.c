int valid_learn(object me)
{
//line number must be same!!!
//so it is done
	//string SKILL_CH_NAME;

	if( (int)me->query("max_neili") < 50 )
		return notify_fail("你的内力太弱，无法练"+SKILL_CH_NAME+"。\n");
	return 1;
}
int valid_enable(string usage)
{
	return usage== SKILL_BASE_NAME || usage=="parry";
}
mapping query_action(object me, object weapon)
{
	//mapping action;
	return action[random(sizeof(action))];
}
int practice_skill(object me)
{
	if( (int)me->query("qi") < 25 )
		return notify_fail("你的体力不够了，休息一下再练吧。\n");
	if( (int)me->query("neili") < 3 )
		return notify_fail("你的内力不够了，休息一下再练吧。\n");
	me->receive_damage("qi", 25);
	me->add("neili", -3);
	return 1;
}
