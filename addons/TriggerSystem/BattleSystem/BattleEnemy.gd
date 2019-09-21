extends BattleCharacter

class_name BattleEnemy

var enemy

func set_enemy(enemy) :
	self.enemy = enemy
	enemy.battle_enemy = self
	face = -1
	name_cn = enemy.name_cn
	set_image(enemy.img)
	hp_max = enemy.hp
	hp = hp_max
	mp_max = enemy.mp
	mp = mp_max
	atk_base = enemy.atk
	def_base = enemy.def
	speed_base = enemy.speed
	skill_list = enemy.skill_list
#
#func _process(delta: float) -> void:
#	enemy.process(delta)