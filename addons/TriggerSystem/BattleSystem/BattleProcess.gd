extends Node

static func damageProcess(dmgObj:DmgObj):
	var from = dmgObj.from
	var to = dmgObj.to
	if to.state == "die" || from.state == "die":
		return
	# 伤害开始前
	TriggerSystem.sendEvent("damage_before",dmgObj)
	# 闪避阶段
	TriggerSystem.sendEvent("dodge",dmgObj)
	if dmgObj.isDodge :
		# 显示闪避效果
		to.dodge()
		return
	# 暴击阶段
	TriggerSystem.sendEvent("crit",dmgObj)
	
	if dmgObj.type == 0 :
		# 正防御
		if to.def > 0 :
			var dr = float(to.def)/(to.def + 100)
			dmgObj.dmg = floor(dmgObj.dmg * (1 - dr))
		# 负防御 （伤害加深）
		elif to.def < 0 :
			var ir = float(abs(to.def))/(abs(to.def) + 100)
			dmgObj.dmg = floor(dmgObj.dmg * (1 + ir))
	else:
		pass
	if dmgObj.dmg < 0 :
		dmgObj.dmg = 0
	# 伤害结算阶段 优先扣除护盾
	if to.shield > 0 :
		if to.shield >= dmgObj.dmg :
			to.shield -= dmgObj.dmg
		else:
			var left = dmgObj.dmg - to.shield
			to.shield = 0
			to.hp -= left
	else :
		to.hp -= dmgObj.dmg
# 受到伤害
	to.beHit(dmgObj)
	# 伤害之后的事件
	TriggerSystem.sendEvent("damage_after",dmgObj)
	
	pass
	
static func healProcess(healObj:HealObj):
	var from = healObj.from
	var to = healObj.to
	if to.state == "die" || from.state == "die" :
		return
	# 治疗开始前
	TriggerSystem.sendEvent("heal_before",healObj)
	# 治疗
	if healObj.heal < 0 : 
		healObj.heal = 0
	to.hp +=  healObj.heal
	# 跳出治疗数字
	to.beHeal(healObj)
	pass
