// blade.c 基本刀法
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
	write(HIC"\n基本刀法："NOR"\n");
	write(@HELP

    刀类武技的基本功。
    刀是历代重要兵器之一，其中大刀被誉为「百兵之帅」。「刀
如猛虎，枪似蛟龙」。刀术的演练一招一式都要有威武、凛烈的气
慨。刀的使用特点是缠头裹脑、翻转劈扫、撩挂云刺、托架抹挑等，
并有单刀看手、双刀看走、大刀看顶手，劈、撩、斩、刺似猛虎之
说。 

	学习要求：
		无
HELP
	);
	return 1;
}

