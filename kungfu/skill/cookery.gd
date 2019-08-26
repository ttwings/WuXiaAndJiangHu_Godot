# cookery.c 烹饪手艺
# Last Modified by winder on Jun. 10 2000

#include <ansi.h>
# inherit SKILL

extends Skill

#func create():
#	seteuid(getuid())

func type(): 
	return "knowledge"
func learn_bonus(): 
	return 30
func practice_bonus(): 
	return 30
func success(): 
	return 30
func power_point(me): 
	return 1

func valid_learn(me):
	return 1

func practice_skill(me = null):
	return notify_fail("烹饪手艺只能靠学习来提高。\n")

func help(me = null):

	write(HIC + "\n烹饪手艺："+ NOR + "\n")
	write("""

    烹饪手艺是你宴请玩家的本钱。请help cookery。

	学习要求：
		无。但天赋才气限制了对更高深境界的努力
"""
	)
	return 1


