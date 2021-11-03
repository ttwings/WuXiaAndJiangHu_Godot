# parry.c 基本招架
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
var parry_msg = [
	"只听见「锵」一声，被$p格开了。\n",
	"结果「当」地一声被$p挡开了。\n",
	"但是被$n用手中兵刃架开。\n",
	"但是$n身子一侧，用手中兵刃格开。\n",
]
var unarmed_parry_msg = [
	"但是被$p格开了。\n",
	"结果被$p挡开了。\n",
]

""" 招架信息 $n的$W: 招架人的兵器 $P的$l和$w: 攻击方的身体部位和兵器 """
var axe_msg = [
	"却见$n踏前一步，举起$W奋力一架，架开了$P的$w。\n",
	"$n侧过头，斜身举起$W，向$P的$l虚劈一斧，迫得$P攻势不由自主停下来！\n",
	"只听见「锵」一声，$n举起$W将$P的$w格开了。\n",
	"结果「当」地一声，$n身子一侧，用手中$W格开$P的$w。\n",
]
var blade_msg = [
	"却见$n踏前一步，抡起$W奋力向上一架，架开了$P的$w。\n",
	"$n侧过头，斜身举起$W，窥得$P的亲切就是一刀，迫得$P不得不停下来！\n",
	"只听见「锵」一声，$n举起$W将$P的$w格开了。\n",
	"结果「当」地一声，$n身子一侧，用手中$W格开$P的$w。\n",
	"$n高举手中$W，不管三七二十一，冲着$P当头劈下，逼得$P手忙脚乱。\n",
]
var club_msg = [
	"却见$n向前踏出一步，双手横过$W奋力一架，正好架开了$P的$w。\n",
	"$n侧身一闪，举起$W，向$P的下盘一棍挑去，迫得$P跳起跃开！\n",
	"$n竖起$W一隔，把$P的$w挡在了外门。\n",
	"$n手握$W往$P当胸一捅，逼得$P抡回$w自救不暇。\n",
]
var dagger_msg = [
	"却见$n踏前一步，举起$W奋力一格，架开了$P的$w。\n",
	"$n忙斜身跃前，手执$W奋不顾身向$P的$l就扎，$P只好跳开避免两败俱伤。\n",
	"$n侧过头，斜身举起$W一架，正架在$P的$w上！\n",
]
var hammer_msg = [
	"却见$n踏前一步，举起$W奋力一砸，砸偏了$P的$w。\n",
	"$n侧身立起$W在身前，一锤正好挡住了$P的$w。\n",
	"$n不管三七二十一，长身提起$W，自上而下一锤下去，迫得$P的$w一个收势退了回去！\n",
]
var hook_msg = [
	"却见$n踏前一步，举起$W奋力一架，架开了$P的$w。\n",
	"$n举起$W一钩，正好钩开了$P的$w！\n",
	"$n侧过头，斜身举起$W，向$P的$l一钩钩去，迫得$P回势自救不迭。\n",
	"$n立起$W一挡，堪堪把$P的$w挡在身外！\n",
]
var spear_msg = [
	"却见$n向前踏出一步，双手横过$W奋力一架，正好架开了$P的$w。\n",
	"$n侧身一闪，横过枪尾，向$P的下盘扫去，迫得$P跳起闪避！\n",
	"$n竖起$W一隔，把$P的$w挡在了外门。\n",
	"$n手握$W，抢先向$P分心就刺，逼得$P抡回$w自救不暇。\n",
]
var staff_msg = [
	"却见$n向前踏出一步，双手横过$W奋力一架，正好架开了$P的$w。\n",
	"$n侧身一闪，横过杖尾，向$P的下盘扫去，迫得$P跳起闪避！\n",
	"$n竖起$W一隔，把$P的$w挡在了外门。\n",
	"$n高举$W，发力向$P全力砸下，逼得$P后跃急避不迭。\n",
]
var stick_msg = [
	"却见$n向前踏出一步，双手横过$W奋力一架，正好架开了$P的$w。\n",
	"$n侧身一闪，横过棒尾，向$P的下盘扫去，迫得$P跳起闪避！\n",
	"$n竖起$W一隔，把$P的$w挡在了外门。\n",
	"$n手握$W往$P当胸一捅，逼得$P抡回$w自救不暇。\n",
]
var sword_msg = [
	"却见$n踏前一步，$W斜指$P的右臂，想要使$P撤回$w闪身而退。\n",
	"$n手中$W疾点$P右手手腕，迫得$P收招撤回$w。\n",
	"$n手中$W横过，剑尖划过$P右臂，迫得$P抡回$w撤招。\n",
	"$n手中$W斜出，指向$P的$w来路，「当」地一声，将它挡了开去。\n",
	"$n一个斜身，手中$W斜斜指向$P的$l，迫得$P回招自救。\n",
	"$n突然一剑点向$P的$l，虽一剑却暗藏无数后着，$P手足无措，攻势不由自主停了下来！\n",
]
var whip_msg = [
	"却见$n踏前一步，$W在半空中化为一圈银芒，落向$P的$l，迫使$P闪身而退。\n",
	"但见$n左腿提膝，手中$W斜指，横向$P的$l，要使$P闪身而退。\n"+ NOR,
	"只见$n上身往左侧一拧，右手$W反手抖动，向$P的$l铰去，暗藏无数后着，$P手足无措，攻势不由自主停了下来！\n",
	"可$n手中$W腾空一卷，一声脆响入磬，猛地向$P劈头打下，吓得$P往后倒退几步。\n",
	"却见$n力贯鞭梢，手中$W舞出满天鞭影，排山倒海般扫向$P的全身，$P一招击下，有如石沉大海，不觉呆住了。\n",
]

func query_parry_msg(object weapon):

	if( weapon )
	
		match (weapon.query("skill_type"))
		
		"axe"   :
			return axe_msg[random(sizeof(axe_msg))]
		"blade" :
			return blade_msg[random(sizeof(blade_msg))]
		"club"  :
			return club_msg[random(sizeof(club_msg))]
		"dagger":
			return dagger_msg[random(sizeof(dagger_msg))]
		"hammer":
			return hammer_msg[random(sizeof(hammer_msg))]
		"hook"  :
			return hook_msg[random(sizeof(hook_msg))]
		"spear" :
			return spear_msg[random(sizeof(spear_msg))]
		"staff" :
			return staff_msg[random(sizeof(staff_msg))]
		"stick" :
			return stick_msg[random(sizeof(stick_msg))]
		"sword" :
			return sword_msg[random(sizeof(sword_msg))]
		"whip"  :
			return whip_msg[random(sizeof(whip_msg))]
		_      :
			return parry_msg[random(sizeof(parry_msg))]
		
	
	else: 
		return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))]

 
func help(me):

	write(HIC + "\n基本招架："+ NOR"\n")
	write("""

	招架的基本功。几乎所有技击技能均能激发为招架。

	学习要求：
		无
"""
	)
	return 1


