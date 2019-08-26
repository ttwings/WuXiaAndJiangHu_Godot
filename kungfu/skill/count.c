// count.c 阴阳八卦
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
	object ob;

	mapping myfam;
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "桃花岛"|| myfam["master_id"] != "huang yaoshi")
		return notify_fail("只有黄药师的弟子才能学阴阳八卦。\n");
	if( (int)me->query_skill("literate",1) < 50 )
		return notify_fail("你的读书写字太低，没有办法学阴阳八卦。\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("阴阳八卦只能用学(learn)的来增加熟练度。\n");
}
int help(object me)
{
	write(HIC"\n阴阳八卦："NOR"\n");
	write(@HELP

    桃花岛弟子可以凭此技能查知玩家目前所在的位置。可以通过
阅读《河图》、《洛书》提高。
    请help location。

	学习要求：
		读书写字50级
		身为黄药师嫡传弟子
HELP
	);
	return 1;
}

