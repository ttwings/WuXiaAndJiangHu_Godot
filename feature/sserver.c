// sserver.c

inherit F_CLEAN_UP;

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
	int sz,i;
	object *enemy;

	enemy = me->query_enemy();
	if( !enemy || !arrayp(enemy) ) return 0;
/*  for (i=0;i<sizeof(enemy);i++)
  	if (environment(enemy[i])!=environment(me))
  	 enemy -= ({enemy[i]});

*/	sz = sizeof(enemy);
	if( sz > 4 ) sz = 4;

	if( sz > 0 ) return enemy[random(sz)];
	else return 0;
}
