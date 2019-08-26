# count.c 阴阳八卦
# Last Modified by winder on Mar. 10 2000

#include <ansi.h>
# inherit SKILL

func type(): 
	return "knowledge"
func learn_bonus(): 
	return 0
func practice_bonus(): 
	return 0
func success(): 
	return 10
func power_point(me): 
	return 1

func skill_improved(me):
	pass

func valid_learn(me):
	var ob
	var myfam
	myfam = (mapping)me.query("family")
	if(!myfam || myfam["family_name"] != "桃花岛"|| myfam["master_id"] != "huang yaoshi")
		return notify_fail("只有黄药师的弟子才能学阴阳八卦。\n")
	if( me.query_skill("literate",1) < 50 )
		return notify_fail("你的读书写字太低，没有办法学阴阳八卦。\n")
	return 1


func practice_skill(me):
	return notify_fail("阴阳八卦只能用学(learn)的来增加熟练度。\n")

func help(me):

	write(HIC + "\n阴阳八卦："+ NOR"\n")
	write("""

    桃花岛弟子可以凭此技能查知玩家目前所在的位置。可以通过
阅读《河图》、《洛书》提高。
    请help location。

	学习要求：
		读书写字50级
		身为黄药师嫡传弟子
"""
	)
	return 1


