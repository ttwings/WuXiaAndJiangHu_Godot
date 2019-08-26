// hook.c 基本钩法
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
	write(HIC"\n基本钩法："NOR"\n");
	write(@HELP

    钩类武技的基本功。

	学习要求：
		无
HELP
	);
	return 1;
}
