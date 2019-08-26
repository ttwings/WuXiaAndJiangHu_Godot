// force.h

varargs int valid_public(object me,mixed comb)
{
	mapping skl = me->query_skills();
	string *sk;
	int i;
	string skl_name = explode(__FILE__, "/")[<1][0..<3];
  string* can_skill;
  
  can_skill = ({ "shenzhao-jing" , "taixuan-gong" });
  can_skill += ({ skl_name });
  if (stringp(comb)) can_skill += ({comb});
  if (arrayp(comb)) can_skill += comb;
  
	if (!mapp(skl)) return 1;
	if (SCBORN_D->valid_learn(me,skl_name)) return 1;
	sk = keys(skl);
	i = sizeof(sk);
	while (i--)
	{
		if (SKILL_D(sk[i])->valid_enable("force"))
			if ( member_array(sk[i],can_skill) == -1 )
		     	     if (!SCBORN_D->valid_learn(me,sk[i])) 
				return notify_fail("你不散掉"+to_chinese(sk[i])
					+"，如何能修习"+to_chinese(skl_name)+"。\n");
	}
	return 1;
}
