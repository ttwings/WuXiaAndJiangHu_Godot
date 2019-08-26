# finger.c 基本指法
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
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
func power_point(me): 
	return 1

func help(me):
	write(HIC + "\n基本指法："+ NOR"\n")
	write("""
    指法类武技的基本功，并能改善你后天的膂力。
	学习要求：
		无
"""
	)
	return 1


