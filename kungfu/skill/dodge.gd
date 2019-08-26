# dodge.c 基本轻功
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
extends Skill

func type(): 
	return "martial"
func martialtype(): 
	return "dodge"
func learn_bonus(): 
	return 30
func practice_bonus(): 
	return 30
func success(): 
	return 30
func power_point(me): 
	return 1

var dodge_msg = [
	"但是和$p$l偏了几寸。\n",
	"但是被$p机灵地躲开了。\n",
	"但是$n身子一侧，闪了开去。\n",
	"但是被$p及时避开。\n",
	"但是$n已有准备，不慌不忙的躲开。\n",
]

func query_dodge_msg():
	return dodge_msg[random(sizeof(dodge_msg))]

func help(me):
	write(HIC + "\n基本轻功："+ NOR"\n")
	write("""
    轻功类武技的基本功，并能改善你后天的身法。
    轻功高到一定程度可以轻易渡河(cross)，练习一些特别的轻功
将更为容易达到过河条件。

	学习要求：
		无
"""
	)
	return 1


