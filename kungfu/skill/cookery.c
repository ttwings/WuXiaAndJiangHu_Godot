// cookery.c 烹饪手艺
// Last Modified by winder on Jun. 10 2000

#include <ansi.h>
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
	return 1;
}
int practice_skill(object me)
{
	return notify_fail("烹饪手艺只能靠学习来提高。\n");
}
int help(object me)
{
	write(HIC"\n烹饪手艺："NOR"\n");
	write(@HELP

    烹饪手艺是你宴请玩家的本钱。请help cookery。

	学习要求：
		无。但天赋才气限制了对更高深境界的努力
HELP
	);
	return 1;
}

