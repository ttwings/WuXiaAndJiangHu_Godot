// alias.c
// From ES2
// Modified for XKX by Xiang (12/15/95)
// Last Modified for XKX100 by Winder (05/17/2001)
#pragma save_binary

#define MAX_REPEAT 30
#define MAX_ALIASES 40
#define HISTORY_BUFFER_SIZE 10
#define MAX_IN_A_ROW 20
#include <ansi.h>

mapping alias;

static string *history, last_input;
static int last_cmd, repeat_cnt = 0;
static int last_check, maxcom = 0;

string process_input(string str)
{
	string *args, cmd, argstr, badstr;
	int i, j;
	object me = this_object();

/* 限制蹩脚机器人
	if(maxcom == 0) last_check = time();
	if(maxcom == (MAX_IN_A_ROW - 1) && time() == last_check)
	{
		me->start_busy(1);
		return "";
	}
	else
		maxcom++;
	maxcom = maxcom % MAX_IN_A_ROW ;
*/
// 限制disable_player后遗症
	if( !interactive(me) ) command("quit");       // 非交互物品
	if( !query_heart_beat(me) ) command("quit");  // 无心跳
	if( !living(me)) return "";                   // 不是活物
	if( me->query_temp("noliving") ) return "";   // 非活动玩家
	if( !wizardp(me))
	{
		if (me->query("jing") < 0 || me->query("qi") < 0)
		{
			write("你马上要昏迷了，不能做任何事情。\n");
			return "";
		}
	}
// 限制粗口 
	badstr=lower_case(str);
        badstr = replace_string(badstr, "$blk$", "");
        badstr = replace_string(badstr, "$red$", "");
        badstr = replace_string(badstr, "$grn$", "");
        badstr = replace_string(badstr, "$yel$", "");
        badstr = replace_string(badstr, "$blu$", "");
        badstr = replace_string(badstr, "$mag$", "");
        badstr = replace_string(badstr, "$cyn$", "");
        badstr = replace_string(badstr, "$wht$", "");
        badstr = replace_string(badstr, "$hir$", "");
        badstr = replace_string(badstr, "$hig$", "");
        badstr = replace_string(badstr, "$hiy$", "");
        badstr = replace_string(badstr, "$hib$", "");
        badstr = replace_string(badstr, "$him$", "");
        badstr = replace_string(badstr, "$hic$", "");
        badstr = replace_string(badstr, "$hiw$", "");
        badstr = replace_string(badstr, "$nor$", "");
        badstr = replace_string(badstr, "$blink$", "");

	if( !wizardp(me) && strsrch(badstr, "fuck") >= 0)
	{
		me->add_temp("fuck", 1);
		if (me->query_temp("fuck") > 1)
			return "";
		message("channel:chat", HIC"【闲聊】"+me->name()+"张开大嘴放了个冲天大臭屁，结果一口气没上来，就被自己的大粪给活活憋死了。\n"NOR, users());
		return "";
	}
// 限制非法获取的生命数据
	if( userp(me) )
	{
		if((int)me->query("eff_qi") > (int)me->query("max_qi"))
			me->set("eff_qi", me->query("max_qi"));
		if((int)me->query("qi") > (int)me->query("eff_qi"))
			me->set("qi", me->query("eff_qi"));
		if((int)me->query("eff_jing") > (int)me->query("max_jing"))
			me->set("eff_jing", me->query("max_jing"));
		if((int)me->query("jing") > (int)me->query("eff_jing"))
			me->set("jing", me->query("eff_jing"));
		if((int)me->query("neili") > (int)me->query("max_neili") * 2)
			me->set("neili", (int)me->query("max_neili") * 2);
	}
// 限制频道字符和其他泥巴宣传
	if( !wizardp(me) && (strsrch(str, "[") >= 0 || strsrch(str, "%") >= 0 || strsrch(str, "5555") >= 0 || strsrch(str, "8888") >= 0 || strsrch(str, "6666") >= 0 || strsrch(str, "9999") >= 0)) return "";
// 限制太多的命令输入行
	if( str==last_input && str != "" )
	{
		repeat_cnt++;
		if( repeat_cnt > MAX_REPEAT )
		{
			tell_object(me,"\n天后仙子突然在一阵烟雾中出现：你重复命令太多，最后那些都失效了！！\n\n");
//			command("quit");
			if(!me->is_busy()) me->start_busy(random(10));
			return "";
		}
	}
	else
	{
		repeat_cnt = 0;
		if (str != "")
		{last_input = str;}
	}

	if( str[0]=='!' ) {
		if( pointerp(history) && sizeof(history) ) {
			if( sscanf(str, "!%d", i) )
				str = (string)history[(HISTORY_BUFFER_SIZE + last_cmd - i) % HISTORY_BUFFER_SIZE];
			else
				str = history[last_cmd];
		} else
			return "";
	} else {
		if( !pointerp(history)) history = allocate(HISTORY_BUFFER_SIZE);
		last_cmd = (last_cmd + 1) % HISTORY_BUFFER_SIZE;
		history[last_cmd] = str;
	}

	if( mapp(alias) )
	{
		if( !undefinedp(alias[str]) )
			return replace_string( alias[str], "$*", "" );

		if( sscanf(str, "%s %s", cmd, argstr)==2 && !undefinedp(alias[cmd]) ) {
			cmd = replace_string( alias[cmd], "$*", argstr );
			args = explode(argstr, " ");
			if( (j = sizeof(args)) )
				for(i=0; i<j; i++)
					cmd = replace_string( cmd, "$" + (i+1), args[i] );
			return cmd;
		}
	}
	return (string)ALIAS_D->process_global_alias(str);
}

int set_alias(string verb, string replace)
{
	if( !replace ) {
		if( mapp(alias) ) map_delete(alias, verb);
		return 1;
	} else {
		if( !mapp(alias) ) alias = ([ verb:replace ]);
		else if( sizeof(alias) > MAX_ALIASES )
			return notify_fail("您设定的 alias 太多了，请先删掉一些不常用的。\n");
		else alias[verb] = replace;
		return 1;
	}
}

mapping query_all_alias()
{
	return alias;
}

