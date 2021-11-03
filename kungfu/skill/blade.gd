# blade.c 基本刀法
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
# inherit SKILL;
extends Skill

func type():
	return "martial"
func martialtype():
	return "skill"

func learn_bonus():
	return 30
func practice_bonus():
	return 30
func success():
	return 30
func power_point(me=null):
	return 1

func help(me=null):
	write(HIC + "\n基本刀法："+ NOR + "\n")
	
	write("""
	刀类武技的基本功。
	刀是历代重要兵器之一，其中大刀被誉为「百兵之帅」。「刀
如猛虎，枪似蛟龙」。刀术的演练一招一式都要有威武、凛烈的气
慨。刀的使用特点是缠头裹脑、翻转劈扫、撩挂云刺、托架抹挑等，
并有单刀看手、双刀看走、大刀看顶手，劈、撩、斩、刺似猛虎之
说。

	学习要求：
		无
""")
	return 1

