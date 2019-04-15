#include <ansi.h>

object load_data(object user,object ob);         //从login ob中读取data
object load_skill(object user);                  //从data中读取skill
object check_user(object user,object ob);        //供logind.c调用
int valid_scborn(object ob);                     //是否可以转生 供外部调用
int save_data(object user,string arg);           //保存指定数据到loginob
varargs int save_skill(object user,string arg,int lvl);//保存指定skill到login
int save_force(object user);                     //保存所有内功到login
int save_knowledge(object user);                 //保存所有知识技能到login
varargs int save_perform(object user,string skill,string pfm);//保存一个技能的pfm到login
int valid_perform(object me,string base_skill,string pfm);//外部调用 是否是保存的pfm
int query_scborn_times(object me);               //外部调用 转生次数
varargs int reborn(object user,string skill,string etc1,string etc2);//各级转生保存数据

void create()
{
	seteuid(ROOT_UID);
}

object check_user(object user,object ob)
{
	log_file("scborn",sprintf("scborn login ob %8s first login from %15s on [%s]\n",ob->query("id"),query_ip_number(ob),ctime(time())));
	user = load_data(user,ob);
	user = load_skill(user);
	return user;
}
object load_data(object user,object ob)
{
	mapping ob_data;
	string *obd;
	int i;
	
	ob_data = ob->query("scborn/data");
	if (!mapp(ob_data)) return user;
	obd = keys(ob_data);
	for (i=0;i<sizeof(obd);i++)
		user->set(obd[i],ob_data[obd[i]]);
	ob->delete("scborn/data");
	user->set("combat_exp",100000);
	user->set("potential",50000);
	return user;
}

object load_skill(object user)
{
	int i;
	mapping skl;
	string *skname;
	
	skl = user->query("scborn/skill");
	if (!mapp(skl)) return user;
	skname = keys(skl);
	for (i=0;i<sizeof(skl);i++)
		user->set_skill(skname[i],skl[skname[i]]);
	return user;
}

//string *bid=({"jolin","waiter","solar","dugu"});
int valid_scborn(object ob)
{
	int times;
	int count,i;
	mapping skl;
	string *sklname;
	int needexp,needskill;
	
	times = this_object()->query_scborn_times(ob);
	switch(times)
	{
		case 0: //从未转生过
			needexp = 5000000;
			needskill = 350;
			break;
		case 1:
			needexp = 10000000;
			needskill = 400;
			break;
		case 2:
			needexp = 20000000;
			needskill = 500;
			break;
		case 3:
			needexp = 40000000;
			needskill = 600;
			break;
		case 4:
			needexp = 80000000;
			needskill = 800;
			break;
		case 5:
			needexp = 160000000;
			needskill = 1000;
			break;
		default: 
		return notify_fail("你已经功德圆满了，不需要转生了。\n");
	}
	
	if (ob->query("combat_exp")<needexp)
	return notify_fail("你的经验尚浅，无法转世。\n");
	skl = ob->query_skills();
	if (!mapp(skl)) return notify_fail("你的武功还没到家，多练练吧。\n");
	sklname = keys(skl);
	for (i=0;i<sizeof(skl);i++)
		if (skl[sklname[i]]>=needskill)	count++;
	if (count < 5) return notify_fail("你的武功还没到家，多练练吧。\n");
	if (!ob->query("guangming_winner")) return notify_fail("你未见识过明教光明圣火阵，没资格转生。\n");
	if (!ob->query("luohan_winner")) return notify_fail("你未见识过少林十八罗汉阵，没资格转生。\n");
	if (!ob->query("qixing")) return notify_fail("你未见识过全真天罡北斗阵，没资格转生。\n");
	if (!ob->query("KILLER")) return notify_fail("你知道大宗师长什么样吗？\n");
	if (ob->query("KILLER") < needskill*(times+1)*(times+1)/10) return notify_fail("宗师对你的评价太差了，再努力一把吧。\n");
//	if ((int)ob->query("gift/qingyun")< 500 * (times+1) ) return notify_fail("你在线完成任务次数太少，不能转生。\n");
//	if (member_array(getuid(ob),bid)>=0)
//  return notify_fail("你的转生条件不够，没法转生。\n");

	return 1;
}

int save_data(object user,string arg)
{
	object ob;
		
	ob = user->query_temp("link_ob");
	if (user->query(arg))
		ob->set("scborn/data/"+arg,user->query(arg));
	return 1;
}

varargs int ssave(object user,string arg,int lvl)
{
	object ob;
	int i;
	
	ob = user->query_temp("link_ob");
	if (!file_size(SKILL_D(arg))) return 0;
	
	if ( intp(lvl) && lvl > 0)  lvl = user->query_skill(arg,1);
	else lvl = 10;
	ob->set("scborn/data/scborn/skill/"+arg,lvl);
	return 1;
}

varargs int save_skill(object user,string arg,int lvl)
{
	object ob;
	int i;
	mapping skl;
	string *sname;
		
	if (arg == "all")
	{
		skl = user->query_skills();
		if (sizeof(skl))
		{
			sname = keys (skl);
			for (i=0;i<sizeof(skl);i++)
			{
				if (SKILL_D(sname[i])->type() == "knowledge")
					ssave(user,sname[i],1);
				else 
					ssave(user,sname[i]);
			}
		}
	}
	else if (intp(lvl) && lvl > 0)
		ssave(user,arg,lvl);
	else
		ssave(user,arg);
	return 1;
}

int save_force(object user)
{
	mapping skl;
	string *sname;
	int i;
	
	skl = user->query_skills();
	if (!skl) return 1;
	sname = keys(skl);
	for (i=0;i<sizeof(sname);i++)
	{
		if (SKILL_D(sname[i])->valid_enable("force"))
			save_skill(user,sname[i]);
	}
	return 1;
}

int save_knowledge(object user)
{
	mapping skl;
	string *sname;
	int i;
	
	skl = user->query_skills();
	if (!skl) return 1;
	sname = keys(skl);
	for (i=0;i<sizeof(sname);i++)
	{
		if ((SKILL_D(sname[i])->type())=="knowledge")
			save_skill(user,sname[i],1);
	}
	return 1;
}

varargs int save_perform(object user,string skill,string pfm)
{
	object ob;
	int i;
	mixed dir;
	
	ob = user->query_temp("link_ob");
	if (!stringp(skill)) return 0;
	if (!file_size(SKILL_D(skill))) return 0;
	if (skill == "all")	{
		ob->set("scborn/data/scborn/perform/all",1);
		return 1;
	}
	if (stringp(pfm))	{
		if (!file_size(SKILL_D(skill+"/"+pfm))) return 0;
		if (!user->query("perform/"+pfm)
		&& !SCBORN_D->valid_perform(user,skill,pfm)) return 1;
		ob->set("scborn/data/scborn/perform/"+skill+"."+pfm,1);
		return 1;
	}
	dir = get_dir("kungfu/skill/"+skill+"/");
	for(i=0;i<sizeof(dir);i++)
	{
		pfm = dir[i];
		if (pfm[<2..<1]==".c") pfm = pfm[0..<3];
		if (user->query("perform/"+pfm)==1 || 
		  this_object()->valid_perform(user,skill,pfm))
			ob->set("scborn/data/scborn/perform/"+skill+"."+pfm,1);
	}
	return 1;
}

int valid_perform(object me,string special_skill,string pfm)
{
	if (!special_skill) return 0;
	if (me->query("scborn/perform/all")==1)
		return 1;
	if (me->query("scborn/perform/"+special_skill+"."+pfm)==1)
		return 1;
	return 0;
}
int valid_learn(object me,string skill)
{
	if (me->query("scborn/skill/all")==1)
	return 1;
	if (me->query("scborn/skill/"+skill)>0)
	return 1;
	return 0;
}

int query_scborn_times(object me)
{
	if (!objectp(me)) return 0;
	if (!userp(me)) return 0;
	if (!me->query("scborn/times")) return 0;
	return me->query("scborn/times");
}
int sixborn(object me)
{
	return me->query("scborn/times")==6;
}
varargs int reborn(object user,string skill,string etc1,string etc2)
{
	object ob,couple;
	int i,j,times;
	int flag;
	
	ob = user->query_temp("link_ob");
	times = this_object()->query_scborn_times(user);
	
	save_data(user,"board_last_read");   //保存留言版读取信息
	save_data(user,"bug");               //保存bug贡献
	save_data(user,"bug_count");         //保存bug贡献总和
	save_data(user,"home");              //保存房屋
	save_data(user,"weapon");            //保存武器
// 一转 应该是 reborn(user,"taiji-quan","zhen"); 保存taiji-quan和pfm zhen
// 二转 应该是 reborn(user,"taiji-quan","literate"); 保存 两个技能
// 三转 应该是 reborn(user,"taiji-quan","taiji-shengong"); 保存
// 四转 应该是 reborn(user,"taiji-quan","taiji-jian");
// 五转 应该是 reborn(user,"taiji-quan","taiji-jian","huifeng-jian");
// 六转 应该是 reborn(user);
	switch(times)
	{
		case 0:
			save_skill(user,skill);           //保存一个技能100级
			if (stringp(etc1))
				save_perform(user,skill,etc1);  //保存技能的一个pfm
			ob->set("scborn/times",1);        //记录已经转生次数
			break;
		case 1:
			save_skill(user,skill);          //保存一个技能100级
			save_perform(user,skill);	       //以及这个技能的所有pfm
			save_skill(user,etc1,1);           //完整保存一个知识技能
			ob->set("scborn/times",2);       //记录已经转生次数
			break;
		case 2:
			save_skill(user,skill);          //保存一个技能
			save_perform(user,skill);	       //以及这个技能的所有pfm
			save_knowledge(user);            //保存所有知识技能
			save_skill(user,etc1);         //保存一个内功
			ob->set("scborn/times",3);       //记录已经转生次数
			break;
		case 3:
			save_skill(user,skill);          //保存一个技能
			save_perform(user,skill);	       //以及这个技能的所有pfm
			save_skill(user,etc1);           //保存一个技能
			save_perform(user,etc1);         //以及这个技能的所有pfm
			save_force(user);                //保存所有内功
			save_knowledge(user);            //保存所有知识技能
			ob->set("scborn/times",4);       //记录已经转生次数
			break;
		case 4:
			save_skill(user,skill);          //保存一个技能
			save_perform(user,skill);	       //以及这个技能的所有pfm
			save_skill(user,etc1);           //保存一个技能
			save_perform(user,etc1);         //以及这个技能的所有pfm
			save_skill(user,etc2);           //保存一个技能
			save_perform(user,etc2);         //以及这个技能的所有pfm
			save_force(user);                //保存所有内功
			save_knowledge(user);            //保存所有知识技能
			ob->set("scborn/times",5);       //记录已经转生次数
		  break;
		case 5:
			save_skill(user,"all");          //保存所有技能
			save_perform(user,"all");        //保存所有pfm
			ob->set("scborn/times",6);       //记录已经转生次数
		  break;
		default: return notify_fail("超出转生范围。\n");
	}
	ob->set("scborn/reset_gift",1);
	if (ob->query("couple/have_couple"))
	{
		if (!couple = find_player(ob->query("couple/couple_id")))
		{
			flag = 1;
			couple = NPC_D->create_player(ob->query("couple/couple_id"));
		}
		if (objectp(couple))
		{
			couple->delete("couple");
			couple->save();
			tell_object(couple,"你的"+couple->query("couple/couple_gender")+"自杀了，你们的婚姻关系解除了。\n");
			if(flag == 1) destruct(couple);
		}
		ob->delete("couple");
	}
	return ob->save();
}
