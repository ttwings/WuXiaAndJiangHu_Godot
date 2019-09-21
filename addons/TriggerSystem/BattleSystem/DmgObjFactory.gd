 extends Node

# 快速生成普通伤害
static func createAttackDmg(from,to,dmg):
	var dmgObj = DmgObj.new({
		"from":from,
		"to":to,
		"dmg":dmg,
		"canCrit":true,
		"type":0,
		"rebound":true,
		"canDodge":true,
		"isNormalAttack":true
	})
	return dmgObj

#  快速生成真气伤害（主要来自绝招），剑气，掌气	
static func createMagicDmg(from,to,dmg):
	var dmgObj = DmgObj.new({
		"from":from,
		"to":to,
		"dmg":dmg,
		"canCrit":false,
		"type":1,
		"rebound":true,
		"canDodge":true,
		"isNormalAttack":false
	})
	return dmgObj	