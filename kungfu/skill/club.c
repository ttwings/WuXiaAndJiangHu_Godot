// club.c 基本棍法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;

string type() { return "martial"; }
string martialtype() { return "skill"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int help(object me)
{
	write(HIC"\n基本棍法："NOR"\n");
	write(@HELP

    棍类武技的基本功。
    所谓“枪扎一条线，棍打一大片”，一扫一劈全身着力。棍练
起来虎虎生风，节奏生动，棍法密集，快速勇猛。它既能强身健体，
又能克敌制胜，在历代抗敌御侮中，少林棍发挥过重要的作用。 

	学习要求：
		无
HELP
	);
	return 1;
}

