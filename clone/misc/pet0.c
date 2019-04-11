// /clone/misc/pet.c
// Last Modified by Winder on Jul. 15 2001

#include <ansi.h>
#include <combat.h>
#include <skill.h>
inherit NPC;
int restore();
int save();

void create()
{
//	if (!restore()){
	set_name("坐骑", ({"pet"}));
	set("race", "野兽");
	set("age", 1);
	set("mud_age", 1);
	set("combat_exp", 100);
	set("limbs", ({ "头部","身体","前心","后背","前爪","后腿","尾巴" }) );
	set("verbs", ({ "bite", "claw"}));

	set("ride/msg", "骑");
	set("ride/dodge", 5);
	set("curiousness", 1);    // 好学的。可以学习的条件
	set("owner","mudlib");
	set_temp("owner","mudlib");
	set_temp("apply/attack", 5);
	set_temp("apply/armor", 5);
	setup();
//	}
}

void init()
{
	if(this_object()->query_temp("owner") == this_player()->query("id"))
	{
		add_action("do_shape", "shape");
		add_action("do_modify", "modify");
		add_action("do_xunlian", "xunlian");
		add_action("do_order", "order");
//		add_action("do_command", "command");
	}
}
void unconcious()
{
	die();
}
void die()
{	
	int exp;

	message("channel:rumor", HIM"【谣言】某人：听说"+query_temp("ownername")+"的"+name()+"死了，等级下降了。真是可惜。\n"NOR, users());

	exp = (int) query("combat_exp");
	set("combat_exp", exp/10 * 9);
	if( query("level") > 1) add("level",  -1);
	if( query("obe") > 1) add("obe",  -1);
	set("qi", query("eff_qi"));
	set("eff_qi", query("max_qi"));
	set("jing", query("eff_jing"));
	set("eff_jing", query("max_jing"));
	save();
	::die();
}
string query_save_file()
{
	string id;

	id = query("owner");
	if( !stringp(id) ) return 0;
	return sprintf("/data/pet/%c/%s", id[0], id);
}
int save()
{
	string file;

	if( stringp(file = this_object()->query_save_file()) )
	{
		assure_file(file+ __SAVE_EXTENSION__);
		return save_object(file);
	}
	return 0;
}
int restore()
{
	string file;

	if( stringp(file = this_object()->query_save_file()) )
		return restore_object(file);
	return 0;
}
int do_modify(string arg)
{
	string item, msg;
	object me = this_player();

	if(!arg || sscanf(arg,"%s %s", item, msg) != 2)
		return notify_fail("命令错误：modify 款项 内容\n\n\t款项列表：

                    爱称         name
                    绰号         nick
                    细节描述     long
                    逃跑系数     wimpy\n\n");
	if(me->query("jing") < 20)
		return notify_fail("你的精气不足，暂时没法修改宠物。\n");
	if(item == "wimpy")
	{
		set("env/wimpy", atoi(msg));
		write("设定宠物逃跑系数成功。\n");
		return 1;
	}
	msg = replace_string(msg, "$BLK$", BLK);
	msg = replace_string(msg, "$RED$", RED);
	msg = replace_string(msg, "$GRN$", GRN);
	msg = replace_string(msg, "$YEL$", YEL);
	msg = replace_string(msg, "$BLU$", BLU);
	msg = replace_string(msg, "$MAG$", MAG);
	msg = replace_string(msg, "$CYN$", CYN);
	msg = replace_string(msg, "$WHT$", WHT);
	msg = replace_string(msg, "$HIR$", HIR);
	msg = replace_string(msg, "$HIG$", HIG);
	msg = replace_string(msg, "$HIY$", HIY);
	msg = replace_string(msg, "$HIB$", HIB);
	msg = replace_string(msg, "$HIM$", HIM);
	msg = replace_string(msg, "$HIC$", HIC);
	msg = replace_string(msg, "$HIW$", HIW);
	msg = replace_string(msg, "$NOR$", NOR);

	if(item != "nick")
	{
		if(CHINESE_D->check_control(msg))
			return notify_fail("描述文字中不可有控制符。\n");
		if(!CHINESE_D->check_chinese(msg))
			return notify_fail("描述必须是中文。\n");
	}
	if(CHINESE_D->check_space(msg))
		return notify_fail("描述中不能含空格。\n");
	if(CHINESE_D->check_return(msg))
		return notify_fail("描述文字中不能含回车键！\n");
	me->receive_damage("jing", 10);
	switch(item)
	{
		case "name" :
			if(CHINESE_D->check_length(msg) > 10)
				return notify_fail("宠物爱称描述太长！\n");
			set("name",msg);
			me->set("Pet/name",msg+NOR);
			write("宠物爱称设定成功！\n");
			return 1;
		case "nick" :
			if(CHINESE_D->check_length(msg) > 20)
				return notify_fail("宠物绰号描述太长！\n");
			set("nickname",msg+NOR);
			write("宠物绰号设定成功！\n");
			return 1;
		case "long":
			if(CHINESE_D->check_length(msg) > 100)
				return notify_fail("宠物细节描述太长！\n"); 
			set("long",msg+"\n"+NOR);
			write("宠物细节设定成功！\n");
			return 1;
	}
	return notify_fail("你要修改什么？\n");
}
int do_xunlian(string arg)
{
	object me = this_player(), pet = this_object();
	int jing_cost, amount, exp, myskill, itskill;

	if(!arg || arg == "")
		return notify_fail("你要训练宠物什么技能呢？\n");
	if(!myskill = me->query_skill(arg,1))
		return notify_fail("这项技能你好象还不会呢！\n");
	if(arg != "unarmed" && arg != "dodge" && arg != "parry")
		return notify_fail("它学不会这项技能的！\n");
	itskill = query_skill(arg, 1);
	if(myskill <= itskill)
		return notify_fail( name()+"以嘲笑的目光望着你：你还没我牛呢，想教我？！\n");
	if(me->is_busy())
		return notify_fail("你的动作还没有完成，不能教导宠物。\n");
	if(me->is_fighting() )
		return notify_fail("你已经在战斗中了，还想教导宠物？\n");
	if(pet->is_busy())
		return notify_fail("它的动作还没有完成，不能学习。\n");
	if(pet->is_fighting() )
		return notify_fail("他已经在战斗中了，还想学习？\n");
	if((int)me->query("potential")-(int)me->query("learned_points") < 1)
		return notify_fail("你的潜能不够。\n");
	jing_cost = (int) query_int();
	if((int)me->query("jing") < jing_cost)
		return notify_fail("你显然太累了，没有办法继续教！\n");
	me->receive_damage("jing",jing_cost);
	amount = (int)((me->query("int") + query("int"))/3);
	message_vision(sprintf("$N不厌其烦地教$n「%s」。\n",to_chinese(arg)), me, pet);
	if(random(100) > query("obe") )
	{
		message_vision("$N很不情愿地哼了一声。\n", pet);
		return 1;
	}
	else 
	{
		exp = pet->query("combat_exp");
		if( itskill * itskill * itskill / 10 < exp)
		{
			pet->improve_skill(arg, amount);
			pet->add("combat_exp", random(5));
			me->add("learned_points", 1);
			message_vision(sprintf("$N似乎真的学会了一些「%s」！\n", to_chinese(arg)), pet);
		}
		else
			message_vision(sprintf("由于经验所限，$N似乎不能理解更高深的「%s」。\n", to_chinese(arg)), pet);
	}
	return 1;

}
string status_color(int current, int max)
{
	int percent;

	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}
int do_shape(string arg)
{
	mapping my;
	string shape;
	int at_pt,pa_pt,do_pt;
	my = query_entire_dbase();

	printf(HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR);
	printf("主人： %s\t\t\t姓名： %s\n"NOR, my["owner"], this_object()->query_temp("ownername"));
	printf("年龄： %d\t种类： %s\t爱称： %s\t绰号： %s\n"NOR, my["age"], my["title"], my["name"], my["nickname"]);
	printf("才智： %d\t体质： %d\t速度： %d\t力量： %d\n",query_int(),query_con(),query_dex(),query_str());
	printf("体态： %d\t灵性： %d\t冒险： %d\t克制： %d\n",query_per(),query_kar(),query_cor(), query_cps());
	printf("驯服： "HIM"%d"NOR"\t杀气： "HIR"%d"NOR"\t经验： "HIG"%d"NOR "\t逃命： "HIC"%d\n"NOR, query_obe(), my["shen"], my["combat_exp"], my["env/wimpy"]);
	at_pt= COMBAT_D->skill_power(this_object(),"unarmed",SKILL_USAGE_ATTACK);
	pa_pt= COMBAT_D->skill_power(this_object(),"parry",SKILL_USAGE_DEFENSE);
	do_pt= COMBAT_D->skill_power(this_object(),"dodge",SKILL_USAGE_DEFENSE);
	printf("攻击： "HIY"%d"NOR"\t防御： "HIC"%d\t"NOR"食物： %s%3d/ %3d\t"NOR"饮水： %s%3d/ %3d\n"NOR,
		at_pt+1, pa_pt/2+do_pt/2+1,
		status_color(my["food"], this_object()->max_food_capacity()),
		my["food"], this_object()->max_food_capacity(),
		status_color(my["water"], this_object()->max_water_capacity()),
		my["water"], this_object()->max_water_capacity());
	printf("精气：%s%3d/ %3d %s(%3d%%)\t\t"NOR"气血：%s%3d/ %3d %s(%3d%%)\n\n"NOR, status_color(my["jing"],my["eff_jing"]),my["jing"],my["eff_jing"], status_color(my["eff_jing"],my["max_jing"]),my["eff_jing"]*100/my["max_jing"], status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"], status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"] );		
	printf(HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR);
	printf("/cmds/skill/skills"->pet_skill(this_object()));
	printf(HIC"≡"HIY"──────────────────────────────"HIC"≡\n"NOR);
	return 1;
}
string *cmds_exclude=({		  //加入被禁止的cmds
	"wiz",
	"sys",
	"go",
});				
int do_command(string arg)
{
	int err, i, j;
	string id, cmd;
	string *cmds;
	object who = this_player();
	object me= this_object();

	if( !arg || sscanf(arg, "%s to %s", id, cmd)!=2)
		return notify_fail("你要命令什么做什么？\n");
	if(id!=(string)me->query("id")) return 0;
	if(who->query("id")!=me->query_temp("owner"))
		return notify_fail("你对"+me->query("name")+"命令了几句，可是它理都不理你。\n");
	tell_object(who,"你命令" +me->name() + "去: " + cmd + "\n");	
	cmds = explode(cmd," ");
	for(i=0;i< sizeof(cmds_exclude);i++)
		if (!strcmp(cmds[0],cmds_exclude[i]))
			j = i;
	if(!strcmp(cmds[0],cmds_exclude[j]))	
		return notify_fail("你胡乱发了几个指令，"+me->query("name")+"瞪着无辜的大眼睛@_@看着你：“我不懂耶....”\n");	
//	err=me->command(cmd);
	return me->force_me(cmd);
/*
	if (!err )
		return notify_fail("你胡乱发了几个指令，"+me->query("name")+"瞪着无辜的大眼睛@_@看着你：“我不懂耶....”\n");
	return 1;
*/
}
int do_order(string arg)
{
	int obedience;
	object me = this_player();

	if(me->query("jing") < 20)
		return notify_fail("你的精气不足，暂时没法使唤宠物。\n");
	me->receive_damage("jing", 5);
	obedience = query("obe");
	if(random(100) < obedience )
		command("emote " + arg);
	else command("emote 很不情愿地哼了一声。");
	return 1;
}
