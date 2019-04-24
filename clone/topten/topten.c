// topten.c
// 1998/12/17 Modified by Winder 增加基本赌技排行榜,zeratul 2000.1.13
// Last Modified by winder on Aug. 5 2001 增加宠物排行

#include <ansi.h>

inherit ITEM;

mapping *exp_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *richman_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *oldman_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *force_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *literate_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *pks_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *killer_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *thief_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *sword_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *blade_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *unarmed_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *dodge_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *throwing_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *whip_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *hammer_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *staff_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *weapon_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *gambling_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *petexp_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *petobe_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *mudage_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *score_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *handsome_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *beauty_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});
mapping *kill_topten =
	({
		(["第1名":"空缺"]),
		(["第2名":"空缺"]),
		(["第3名":"空缺"]),
		(["第4名":"空缺"]),
		(["第5名":"空缺"]),
		(["第6名":"空缺"]),
		(["第7名":"空缺"]),
		(["第8名":"空缺"]),
		(["第9名":"空缺"]),
		(["第10名":"空缺"]),
	});

string *whichpart =
	({
		HIR " 榜次         榜名              排行依据          " NOR,
		HIB "─────────────────────────" NOR,
		HIY "第一榜    十大高手排行榜  ------ 经    验 ----  B1" NOR,
		HIY "第二榜    十大财主排行榜  ------ 存    款 ----  B2" NOR,
		HIY "第三榜    十大寿星排行榜  ------ 年    龄 ----  B3" NOR,
		HIY "第四榜    十大内功高手    ------ 内力修为 ----  B4" NOR,
		HIY "第五榜    十大博学鸿儒    ------ 读书技能 ----  B5" NOR,
		HIY "第六榜    江湖十大冷血    ------ ＰＫ人数 ----  B6" NOR,
		HIY "第七榜    江湖十大杀手    ------ 实战业绩 ----  B7" NOR,
		HIY "第八榜    江湖十大神偷    ------ 偷窃技能 ----  B8" NOR,
		HIY "第九榜    天下十大剑客    ------ 剑法技能 ----  B9" NOR,
		HIY "第十榜    天下十大刀客    ------ 刀法技能 ----  B10" NOR,
		HIY "第十一榜  天下十大神拳    ------ 拳脚技能 ----  B11" NOR,
		HIY "第十二榜  十大逃跑高竿    ------ 轻功技能 ----  B12" NOR,
		HIY "第十三榜  中原十大暗器手  ------ 暗器技能 ----  B13" NOR,
		HIY "第十四榜  中原十神鞭      ------ 鞭法技能 ----  B14" NOR,
		HIY "第十五榜  中原十大锤      ------ 锤法技能 ----  B15" NOR,
		HIY "第十六榜  神州十大杖客    ------ 杖法技能 ----  B16" NOR,
		HIY "第十七榜  环宇十大神兵手  ------ 煅制兵器 ----  B17" NOR,
		HIY "第十八榜  天下十大赌棍    ------ 赌博技能 ----  B18" NOR,
		HIY "第十九榜  天下十大强宠物  ------ 宠物经验 ----  B19" NOR,
		HIY "第二十榜  天下十大乖宠物  ------ 驯服宠物 ----  B20" NOR,
	});
string printdate = NATURE_D->game_time();

void create()
{
	string id;
	int i, exp;

	set_name(HIY "侠客行英雄榜" NOR, ({"hero board", "board"}));
	set_weight(800);
	set("unit", "幅");
	set("long", "这是记载侠客行一百英雄座次排行情况的金榜。你可以用(READ)来查阅。\n");
	set("value", 1600);
	set("no_get", 1);
	set("no_steal", 1);
	set("no_put", 1);
	set("no_beg", 1);
	set("material", "paper");
}
void init()
{
	object ob, me = this_object();

	seteuid(getuid());
	if (ob = new ("/clone/topten/magic-rice"))
		if ((exp_topten = ob->query("exp_topten")) &&
			(richman_topten = ob->query("richman_topten")) &&
			(oldman_topten = ob->query("oldman_topten")) &&
			(force_topten = ob->query("force_topten")) &&
			(literate_topten = ob->query("literate_topten")) &&
			(pks_topten = ob->query("pks_topten")) &&
			(killer_topten = ob->query("killer_topten")) &&
			(thief_topten = ob->query("thief_topten")) &&
			(sword_topten = ob->query("sword_topten")) &&
			(blade_topten = ob->query("blade_topten")) &&
			(unarmed_topten = ob->query("unarmed_topten")) &&
			(dodge_topten = ob->query("dodge_topten")) &&
			(throwing_topten = ob->query("throwing_topten")) &&
			(whip_topten = ob->query("whip_topten")) &&
			(hammer_topten = ob->query("hammer_topten")) &&
			(staff_topten = ob->query("staff_topten")) &&
			(weapon_topten = ob->query("weapon_topten")) &&
			(gambling_topten = ob->query("gambling_topten")) &&
			(petexp_topten = ob->query("petexp_topten")) &&
			(petobe_topten = ob->query("petobe_topten")) &&
			(mudage_topten = ob->query("mudage_topten")) &&
			(score_topten = ob->query("score_topten")) &&
			(handsome_topten = ob->query("handsome_topten")) &&
			(beauty_topten = ob->query("beauty_topten")) &&
			(kill_topten = ob->query("kill_topten")))
			destruct(ob);
		else
			write(CYN "\n江湖排行榜出现错误！请通知天帝。\n\n" NOR);
	else
		write(CYN "\n江湖排行榜出现错误！请通知天帝。\n\n" NOR);

	add_action("do_read", "read");
}

int do_read(string arg)
{
	int i;
	string si;
	string *c_short = ({
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
		"空缺",
	});

	switch (arg)
	{
	case "hero board":
	case "board":
	case "b":
	case "侠客行英雄榜":
		write("--------------------------------------------------------\n");
		for (i = 0; i < sizeof(whichpart); i++)
			write("    " + whichpart[i] + "\n");
		write("--------------------------------------------------------\n");
		write("                          ----" + printdate + "公告\n");
		write("你要阅读第几榜？\n");
		break;
	case "B1":
	case "b1":
	case "第一榜":
	case "十大高手排行榜":
		write("                    『" + HIC "十大高手排行榜" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(exp_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B2":
	case "b2":
	case "第二榜":
	case "十大财主排行榜":
		write("                    『" + HIC "十大财主排行榜" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(richman_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B3":
	case "b3":
	case "第三榜":
	case "十大寿星排行榜":
		write("                    『" + HIC "十大寿星排行榜" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(oldman_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B4":
	case "b4":
	case "第四榜":
	case "十大内功高手":
		write("                    『" + HIC "十大内功高手" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(force_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B5":
	case "b5":
	case "第五榜":
	case "十大博学鸿儒":
		write("                    『" + HIC "十大博学鸿儒" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(literate_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B6":
	case "b6":
	case "第六榜":
	case "江湖十大冷血":
		write("                    『" + HIC "江湖十大冷血" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(pks_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B7":
	case "b7":
	case "第七榜":
	case "江湖十大杀手":
		write("                    『" + HIC "江湖十大杀手" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(killer_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B8":
	case "b8":
	case "第八榜":
	case "江湖十大神偷":
		write("                    『" + HIC "江湖十大神偷" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(thief_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B9":
	case "b9":
	case "第九榜":
	case "天下十大剑客":
		write("                    『" + HIC "天下十大剑客" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(sword_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B10":
	case "b10":
	case "第十榜":
	case "天下十大刀客":
		write("                    『" + HIC "天下十大刀客" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(blade_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B11":
	case "b11":
	case "第十一榜":
	case "天下十大神拳":
		write("                    『" + HIC "天下十大神拳" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(unarmed_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B12":
	case "b12":
	case "第十二榜":
	case "十大逃跑高竿":
		write("                    『" + HIC "十大逃跑高竿" NOR + "』\n");
		write("--------------------------------------------------------\n");
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(dodge_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B13":
	case "b13":
	case "第十三榜":
	case "中原十大暗器手":
		write("                    『" + HIC "中原十大暗器手" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(throwing_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B14":
	case "b14":
	case "第十四榜":
	case "中原十神鞭":
		write("                    『" + HIC "中原十神鞭" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(whip_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B15":
	case "b15":
	case "第十五榜":
	case "中原十大锤":
		write("                    『" + HIC "中原十大锤" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(hammer_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B16":
	case "b16":
	case "第十六榜":
	case "神州十大杖客":
		write("                    『" + HIC "神州十大杖客" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(staff_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B17":
	case "b17":
	case "第十七榜":
	case "环宇十大神兵手":
		write("                    『" + HIC "环宇十大神兵手" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(weapon_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B18":
	case "b18":
	case "第十八榜":
	case "天下十大赌棍":
		write("                    『" + HIC "天下十大赌棍" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(gambling_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B19":
	case "b19":
	case "第十九榜":
	case "天下十大强宠物":
		write("                    『" + HIC "天下十大强宠物" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(petexp_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B20":
	case "b20":
	case "第二十榜":
	case "天下十大乖宠物":
		write("                    『" + HIC "天下十大乖宠物" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(petobe_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B21":
	case "b21":
	case "第二十一榜":
	case "天下十大长者":
		write("                    『" + HIC "天下十大长者" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(mudage_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B22":
	case "b22":
	case "第二十二榜":
	case "天下十大愤青":
		write("                    『" + HIC "天下十大愤青" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(score_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;

	case "B23":
	case "b23":
	case "第二十三榜":
	case "天下十大帅哥":
		write("                    『" + HIC "天下十大帅哥" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(handsome_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B24":
	case "b24":
	case "第二十四榜":
	case "天下十大美女":
		write("                    『" + HIC "天下十大美女" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(beauty_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	case "B25":
	case "b25":
	case "第二十五榜":
	case "天下十大杀人狂":
		write("                    『" + HIC "天下十大杀人狂" NOR + "』\n");
		write("--------------------------------------------------------\n");
		si = "名次";
		for (i = 0; i < 10; i++)
		{
			si = sprintf("第%d名", i + 1);
			sscanf(kill_topten[i][si], "%*s\n%s\n%*d\n", c_short[i]);
			write("    " + HIY "第" + chinese_number(i + 1) + "名  " + NOR + c_short[i] + NOR "\n");
		}
		write("========================================================\n");
		break;
	default:
		return 0;
	}
	return 1;
}
