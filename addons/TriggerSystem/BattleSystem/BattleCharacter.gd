extends Node2D

class_name BattleCharacter

# ------ 信号 --------------
signal attack
signal state_change
signal jumpNumber
signal jumpSkillName
signal jumMiss
signal property_change
signal buff_append(buff)
signal buff_remove(buff)
signal item_append(item)
signal item_remove(item)
signal die(character)

# ----------战斗系统 -----------
var battle
var oppent:BattleCharacter = null

# --------- 属性 ----------------
var name_cn = ""
var face = 1

var hp = 100 setget set_hp
var hp_max = 100
var mp = 100 setget set_mp
var mp_max =  100
var shield = 0 setget set_shield

# 根据buff来计算的属性
var atk_base = 10
var atk = 10
var speed_base  = 100
var speed = 100
var def_base = 10
var def = 10

var buff_list = []
var skill_list = []
var item_list = []

# 攻击间隔

func get_attack_interval():
	return 100
	
var attack_timer = 100
# idle、attack、die
var state = "idle" setget set_state
var start_pos:Vector2

# --- 引用 ------
var tween:Tween

# --------
func _ready() -> void:
	tween = $Tween
	start_pos = position
	
func _process(delta: float) -> void:
	$Label.text = state
	match state :
		"idle" :
			attack_timer -= delta * speed
			if attack_timer <= 0 :
				attack()
		"attack" :
			pass
		"die" :
			pass
	for buff in buff_list :
		buff.life -= delta
		if buff.life <= 0 :
			buff_remove(buff)
	for skill in skill_list :
		if skill.cd_timer > 0 :
			skill.cd_timer -= delta
		if skill.cd_timer < 0 :
			skill.cd_timer = skill.cd
	for item in item_list :
		if item.cd_timer > 0 :
			item.cd_timer -= delta
		if item.cd_timer < 0 :
			item.cd_timer = item.cd		

	 						
func start(battle,oppent):
	self.battle = battle
	self.oppent = oppent
	skill_init()
	item_init()
	calculate_property()
	attack_timer = get_attack_interval()
	start_pos = position
	set_state("idle")	
	
# ---- setter -----
func set_state(value):
	state = value
	
func set_hp(value:int):
	hp =  value
	if hp > hp_max :
		hp = hp_max
	emit_signal("state_change")
	if hp <= 0 :
		die()
	
func set_mp(value:int):
	mp = value
	if mp > mp_max :
		mp = mp_max
	emit_signal("state_change")
	
func set_shield(value:int):
	shield = value
	emit_signal("state_change")
	
func set_red(value):
	if value == true :
		$icon.modulate = Color.red
	else:
		$icon.modulate = Color.white

func set_image(image):
	$icon.texture = image
	
func attack():
	set_state("attack")
	var animation_time = 0.4 * (1-float(speed)/(speed + 100))
	tween.interpolate_property(self,"position",position,position + Vector2(50,0)*face,animation_time,Tween.TRANS_LINEAR,Tween.EASE_IN)
	tween.start()
	yield(tween,"tween_completed")
	# 状态不对，取消
	if state == "die" :
		return
	emit_signal("attack",self.oppent)
	TriggerSystem.sendEvent("attack",self)
	tween.interpolate_property(self,"position",position,start_pos,animation_time,Tween.TRANS_LINEAR,Tween.EASE_IN)
	tween.start()
	yield(tween,"tween_completed")
	# 重置攻击计时
	attack_timer = get_attack_interval()
	# 状态不对，取消
	if state == "die" :
		return
	# 切换回等待状态
	set_state("idle")
	
#  受到攻击
func on_hit(dmgObj:DmgObj):
	set_red(true)
	emit_signal("jumpNumber",dmgObj.position)
	yield(get_tree().create_timer(0.2),"timeout")
	set_red(false)
# 受到治疗
func be_heal(healObj:HealObj):
	emit_signal("jumpNumber",healObj.position)				
# 闪避伤害
func dodge():
	emit_signal("jumMiss",position)
	
func die():
	set_state("die")
	emit_signal("die",self)
	tween.interpolate_property(self,"modulate",null,Color(1,1,1,0),1,Tween.TRANS_LINEAR,Tween.EASE_IN)
	tween.start()
	
# --------------- 功能 ------------
func calculate_property():
	# 属性附加值
	var _atk = 0
	var _atk_percent = 0
	var _def = 0
	var _def_percent = 0
	var _speed = 0
	var _speed_percent = 0
	for buff in buff_list :
		var property = buff.property
		var keys = property.keys()
		for key in keys :
			match key :
				"atk" :
					_atk += property["atk"]
				"atk_percent" :
					_atk_percent += property["atk_percent"]
				"def" :
					_def += property["def"]
				"def_percent" :
					_def_percent += property["def_percent"]
				"speed" :
					_speed += property["speed"]
				"speed_percent" :
					_speed_percent += property["speed_percent"]
	atk = floor(atk_base * (1 + float(_atk_percent)/100) + _atk)
	def = floor(def_base * (1 + float(_def_percent)/100) + _def)
	speed = floor(speed_base * (1 + float(_speed_percent)/100) + _speed)
	emit_signal("property_change")
	
# ---- 初始化技能 -----
func skill_init():
	for skill in skill_list :
		skill.start(self)
		for trigger in skill.trigger_list :
			TriggerSystem.appendTrigger(trigger)
			
# ---- 使用技能 ------
func skill_use(skill:Skill):
	if skill.cd_timer > 0 || skill.cost > mp :
		return
	# 技能使用前
	var skill_obj = {
		"skill":skill,
		"user":self
	} 			
	TriggerSystem.sendEvent("skill_before",skill_obj)
	# --- 减少魔法值 ----
	self.mp -= skill.cost
	# ---- 技能进入冷却 ----
	skill.cd_timer = skill.cd
	# ---- 触发技能效果 -----
	emit_signal("jumpSkillName",skill.name_cn,position)
	skill.use()
	# ----- 发出使用技能后事件 ------
	TriggerSystem.sendEvent("skill_after",skill_obj)
	
# ----- 使用物品 -----
# ----- 初始化物品 -----
func item_init():
	for item in item_list :
		item.start(self)
		for trigger in item.trigger_list :
			TriggerSystem.appendTrigger(trigger)

# ------- 使用 ------------
func item_use(item):
	item = item as Item
	if item.type == 0 :
		return
	if !item.can_battle_use	:
		return
	if item.cd_tiemr > 0 or item.cost > mp :
		return
	if item.is_consume and item.number <= 0 :
		return
	# use
	self.mp -= item.cost
	item.cd_timer = item.cd
	emit_signal("jumpSkillName",item.name_cn,position)
	item.use()
	if item.is_consume :
		item.number -= 1
	if item.will_disapper :
		item_remove(item)
							
func item_remove(item):
	for trigger in item.trigger_list :
		TriggerSystem.removeTrigger(trigger)
#	Global.team.item_remove(item)
	emit_signal("item_remove",item)
	calculate_property() 		

func buff_append(buff):
	# 判断是否有一样的buff
	for bf in buff_list :
		if buff.name_cn == bf.name_cn :
			match buff.add_type :
				"single" :
					pass
				# 更新时间
				"cover" :
					bf.life = buff.life
					return
				# 增加层数
				"increase" :
					bf.number += 1
					if bf.number == bf.number_max :
						bf.number = bf.number_max
						bf.life = buff.life
						buff.connect("property_change",self,"on_buff_property_change")
						return
	buff_list.append(buff)
	buff.start(self)
	# 重新计算属性

func buff_remove(buff) :
	if buff_list.has(buff) :
		buff_list.erase(buff)
		buff.end()
		calculate_property()
		emit_signal("buff_remove",buff)
		
func on_buff_property_change() :
	calculate_property()


