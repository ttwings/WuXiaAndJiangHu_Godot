// QUEST.C for randomly get target npcs.

/*
	usage: get_quest(this_player(), shen type(int), job type(string))
	shen type is either 1 for +shen npcs or -1 for -shen npcs,
	it returns a mapping:
	["id"] for target's id, 
	["name"] for taget's name, 
	["last_id"] for last killing target's id,
	["time"]: for time() + quest time, which = end limit for players.
	["exp_reward"] for exp reward,
	["pot_reward"] for pot reward,
	["type"]: for job type,

	PS: targets in same family as u wont be in the list.
	get_time(quest["time"]) will return the time limit in string.
*/

#include <ansi.h>

mapping get_quest(object me, int shen, string type);
int check(object ob, int myexp, string id, int shen, string fam);
int quest_reward(int exp, int texp);
int is_target(object corpse, object me);
string get_time(int i);
string remove_ansi(string str);
string remove_ansi(string str);

mapping get_quest(object me, int shen, string type)
{
	object target, *living;
	int i,j, exp;
	
	living = livings(); 
	exp = (int)me->query("combat_exp");
	
	for (i=0;i < sizeof(living);i++) // check for the 1st time, random.
	{
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j], exp, me->query_temp("quest/last_id"), 
			!intp(shen)?0:shen>0?1:-1,
			me->query("family/family_name")))
		{
			target = living[j];
			break;
		}
	}
		
	if(!objectp(target)) // random failed, get target by orders.
		for (i=0;i < sizeof(living);i++)
			if(check(living[j],exp,me->query_temp("quest/last_id"), 
				!intp(shen)?0:shen>0?1:-1,
				me->query("family/family_name")))
			{
				target = living[j];
				break;
			}

	if(!objectp(target)) return 0;  // no target at all.

	i = quest_reward(exp, target->query("combat_exp"));  // get the rewards.
		return ([ 
			"id":         target->query("id"),
			"name":       remove_ansi(target->name()),
			"last_id":    target->query("id"),
			"time":       time()+(i*30),
			"exp_reward": i,
			"pot_reward": i/3 + random(i/3),
			"type":       type,
		]);
}

int check(object ob, int myexp, string id, int shen, string fam)
{
	object room;
	
	if(!objectp(ob) ||
		userp(ob) ||
		ob->query("env/invisibility") ||
		ob->query("no_quest") ||
		// special npcs, like zhong shentong, attacker, biaoshi etc.
		ob->query("id") == id ||
		ob->query("race")!="ÈËÀà" ||
		ob->query("family/family_name") == fam ||
		ob->query("have_master") ||
		ob->query("owner") ||
		ob->query("haojie") ||
		(ob->query("shen") > 0 && shen <= 0) ||
		(ob->query("shen") < 0 && shen >= 0) ||
		ob->query("combat_exp") > myexp*2 ||
		ob->query("combat_exp") <= myexp ||
		!objectp(room=environment(ob)) ||
		room->query("no_fight") ||
		strsrch(file_name(room),"/d/wuguan/") >= 0 ||
		strsrch(file_name(room),"/d/death/") >= 0 ||
		(strsrch(file_name(room),"/d/") != 0 &&
		strsrch(file_name(room),"/u/beyond/") != 0 &&
		strsrch(file_name(room),"/u/explorer/gb/") != 0 ))
		return 0;
	if( ob->query("id") == "mu ren" ||
		ob->query("id") == "yin ren" ||
		ob->query("id") == "jin ren" ||
		ob->query("id") == "shi ren" ||
		ob->query("id") == "heiyi ren" ||
		ob->query("id") == "jiguan ren" ||
		ob->query("id") == "xiangpi ren" ||
		ob->query("id") == "du jiangshi" ||
		ob->query("id") == "zhang men" ||
		ob->query("id") == "menggu bingshi" ||
		ob->query("id") == "menggu jiangling" ||
		ob->query("id") == "menggu gaoshou" ||
		ob->query("id") == "betrayer")
		return 0;
	else return 1;
}

int quest_reward(int exp, int texp)  // need a better form here.
{
	int i = 5;
 
	if( exp >= texp) return 0;   // my exp > target's
	
	i *= 100-(exp * 100 / texp);

	return i; 
}

int is_target(object corpse, object me)
{
	mapping quest;
			
	if ( !mapp(quest = me->query_temp("quest")))
		return 0; // didnt get the job
	if ( quest["time"] < time())
		return -3; // time up.
	if ( quest["type"] != "É±")
		return -1; // job type is not killing
	if ( corpse->query("id") != "corpse")
		return 0; // it's not a corpse.
	if ( corpse->query("victim_id") != quest["id"] ||
		corpse->query("victim_name") != quest["name"] ||
		corpse->query("kill_by") != me)
		return -2; // killed wrong person.
	if ( corpse->query("victim_user"))
		return -4; // killed a player.
	else return 1;
}

string get_time(int i)
{
	return CHINESE_D->chinese_date(i);
}

string remove_ansi(string str)
{
	int i;
	string *color = ({ BLK, RED, GRN, YEL, BLU, MAG, CYN, WHT,
			   HIR, HIG, HIY, HIB, HIM, HIC, HIW,
			   HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
			   BBLK, BRED, BYEL, BBLU, BMAG, BCYN,
			   NOR, BOLD });
			   
	if( !str || !stringp(str) ) return 0;
	i = sizeof(color);
	while( i-- ) {
		str = replace_string(str, color[i], "");
	}
	return str;
}
