# staff.c 基本杖法
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
func power_point(me=null): 
	return 1

func help(me=null):
	write(HIC + "\n基本杖法："+ NOR + "\n")
	write("""

	杖类武技的基本功。

	学习要求：
		无
"""
	)
	return 1


