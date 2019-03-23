// team.c
// Last Modified by winder on Aug. 25 2001
// 修改成员被杀后的bug

#include <command.h>
#include <dbase.h>
#include <origin.h>

static object leader, *team;

int set_leader(object ob)
{
	if( ob==this_object() )
		error("set_leader: Cannot set this_object() as leader.\n");
	leader = ob;
}

object query_leader() { return leader; }

int follow_path(string dir)
{
	//if( (origin()==ORIGIN_LOCAL) || (origin()==ORIGIN_CALL_OUT) ) {
		this_object()->remove_all_enemy();
		return GO_CMD->main(this_object(), dir);
	//}
}

int follow_me(object ob, string dir)
{
	if( !living(this_object()) || this_object()->query_temp("noliving") ||
		ob==this_object() ) return 0;

	if( ob==leader
	||	(query("pursuer") && this_object()->is_killing(ob->query("id")))) {
		if( random(ob->query_skill("move")) > this_object()->query_skill("move") ) {
			remove_call_out("follow_path");
			call_out("follow_path", 1, dir);
			return 1;
		}
		return follow_path(dir);
	}
}

int add_team_member(object ob)
{
	if( ob==this_object() ) return 0;

	if( arrayp(team) ) {
		if( member_array(ob, team)==-1 ) {
			team += ({ ob });
			for(int i=sizeof(team)-1; i>=0; i--)
				team[i]->set_team(team);
		} else
			return 0;
	} else {
		team = ({ this_object(), ob });
		ob->set_team(team);
	}
	return 1;
}

int is_team_leader()
{
	return arrayp(team) && team[0]==this_object();
}

int set_team(object *t)
{
	team = t;
}

varargs int dismiss_team(object ob)
{
	int i;

	if( !arrayp(team) ) return 0;
	team -= ({ 0 });
	
	if( !ob ) {
		if( team[0]==this_object() ) {
			for(i=1; i<sizeof(team); i++)
				team[i]->set_team(0);
		} else {
			for(i=0; i<sizeof(team); i++)
				team[i]->dismiss_team( this_object() );
		}
		team = 0;
	} else
		team -= ({ ob });

	return 1;
}

object *query_team()
{
	return team;
}

