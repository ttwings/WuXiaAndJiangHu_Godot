// skill.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <ansi.h>
#include <dbase.h>

mapping skills;
mapping learned;
mapping skill_map;
mapping skill_prepare;

mapping query_skills() { return skills; }
mapping query_learned() { return learned; }

void set_skill(string skill, int val)
{
	if( !find_object(SKILL_D(skill))
	&&	file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) ) skills = ([ skill: val ]);
	else skills[skill] = val;
}

int delete_skill(string skill)
{
	if( mapp(skills) ) {
		map_delete(skills, skill);
		if( mapp(learned) ) {
			map_delete(learned, skill);
			return undefinedp(learned[skill]);
		}
		return undefinedp(skills[skill]);
	}
	return 0;
}

// This function 'map' a skill <skill> to another skill <mapped_to>.
// If 2nd argument not given, cancel the mapped skill <skill>.
varargs void map_skill(string skill, string mapped_to)
{
	if( !mapped_to && mapp(skill_map) ) {
		map_delete(skill_map, skill);
		return;
	}

	if( !find_object(SKILL_D(skill))
	&&	file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) )
		return;
		
	if( !mapp(skill_map) ) skill_map = ([ skill: mapped_to ]);
	else skill_map[skill] = mapped_to;
}

// This function 'prepare' a skill <skill> to another skill <mapped_to>.
// If 2nd argument not given, cancel the prepared skill <skill>.
varargs void prepare_skill(string skill, string mapped_to)
{
	if( !mapped_to && mapp(skill_prepare) ) {
		map_delete(skill_prepare, skill);
		return;
	}

	if( !find_object(SKILL_D(skill))
	&&	file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !mapp(skills) || undefinedp(skills[mapped_to]) )
		return;
		
	if( !mapp(skill_prepare) ) skill_prepare = ([ skill: mapped_to ]);
	else skill_prepare[skill] = mapped_to;
}

string query_skill_mapped(string skill)
{
	if( mapp(skill_map) && !undefinedp(skill_map[skill]) )
		return skill_map[skill];
	return 0;
}

string query_skill_prepared(string skill)
{
	if( mapp(skill_prepare) && !undefinedp(skill_prepare[skill]) )
		return skill_prepare[skill];
	return 0;
}

varargs int query_skill(string skill, int raw)
{
	if( !raw ) {
		int s;
		
		s = query_temp("apply/" + skill);
		if( mapp(skills) ) {
			s += skills[skill] / 2;
			if( mapp(skill_map) )
				s += skills[skill_map[skill]];
		}
		return s;
	}
	if( mapp(skills) && !undefinedp(skills[skill]) ) return skills[skill];
	return 0;
}

mapping query_skill_map()
{
	return skill_map;
}

mapping query_skill_prepare()
{
	return skill_prepare;
}

int skill_death_penalty()
{
	string *sk;
	int i;

	if( wizardp(this_object()) || !mapp(skills) ) return 0;

	sk = keys(skills);
/*
	if( !mapp(learned) )
		for(i = 0; i<sizeof(sk); i++)
		{
			skills[sk[i]]--;
			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
		}
	else
		for(i = 0; i<sizeof(sk); i++)
		{
//			if( (int)learned[sk[i]] > (skills[sk[i]]+1) * (skills[sk[i]]+1) / 2 )
//				map_delete(learned, sk[i]);
//			else {
//				skills[sk[i]]--;
//				if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
//			}
			skills[sk[i]]--;
			map_delete(learned,sk[i]);
			if( skills[sk[i]]<0 ) map_delete(skills, sk[i]);
		}
*/
		for(i = 0; i<sizeof(sk); i++)
		{
			skills[sk[i]]--;
			if( skills[sk[i]]<0 
			|| (skills[sk[i]]==0 && learned[sk[i]]==0) )
			 {
			 	map_delete(skills, sk[i]);
			  if (mapp(learned))
			   map_delete(learned,sk[i]);
			 }
		}

	skill_map = 0;
	return 1;
}

int skillreincarnate()
{
	string *sk;
	int i;

	sk = keys(skills);
	for(i = 0; i<sizeof(sk); i++) {
		skills[sk[i]]++;
	}
	log_file("skill_re", sprintf("[%s] %s eat %s \n", ctime(time()), geteuid(this_object()),base_name(previous_object())));
	return 1;
}
varargs void improve_skill(string skill, int amount, int weak_mode)
{
	int spi;

//只有玩家和好学的npc才能学习。比如宠物或玩家小孩等。
	if (!userp(this_object()) && !this_object()->query("curiousness"))
		return; 
	if( !find_object(SKILL_D(skill)) &&
		file_size(SKILL_D(skill)+".c") < 0 )
		error("F_SKILL: No such skill (" + skill + ")\n");

	if( !weak_mode || !userp(this_object()) ) {
		if( !mapp(skills) ) skills = ([]);
		if( undefinedp(skills[skill]) ) skills[skill] = 0;
	}

	// Give learning penalty to those learning too much skills.
	spi = this_object()->query_spi();
	if( sizeof(learned) > spi )
		amount /= sizeof(learned) - spi;

	if( !amount ) amount = 1;

	if( !mapp(learned) ) learned = ([ skill : amount ]);
	else (int)learned[skill] += amount;

	if( (!weak_mode || !userp(this_object())) &&
		learned[skill] > (skills[skill] + 1) * (skills[skill] + 1) )
	{
		skills[skill]++;
		learned[skill] = 0;
		tell_object(this_object(), HIC"你的「" + to_chinese(skill) + "」进步了！\n" NOR);
		SKILL_D(skill)->skill_improved(this_object());
	}
}

