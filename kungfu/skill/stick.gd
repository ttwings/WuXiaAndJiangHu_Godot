# stick.c 基本棒法
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
# inherit SKILL

func type():
	return "martial"
func martialtype()::
	return "skill"
func learn_bonus():
	return 30
func practice_bonus():
	return 30
func success():
	return 30
func power_point(me):
	return 1

func help(me):
	write(HIC + "\n基本棒法："+ NOR"\n")
	write("""
	
	棒类武技的基本功。

	学习要求：
		无
"""
	)
	return 1


