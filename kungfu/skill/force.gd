# force.c 基本内功
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
# inherit SKILL
extends Skill
func type():
	return "martial"
func martialtype():
	return "force"

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

func exert_function_file(func func):
	return __DIR__ + "force/" + func


func skill_improved(me)
	pass

func help(me)

	write(HIC + "\n基本内功："+ NOR"\n")
	write("""

    基本内功是所有武功的基础，并能改善你后天的根骨。
    请help neigong。

	学习要求：
		无
	"""
	)
	return 1


