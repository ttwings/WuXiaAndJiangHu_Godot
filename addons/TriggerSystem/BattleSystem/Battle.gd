extends Node2D

# 战斗系统
class_name Battle

signal win
signal loose

# turn
signal player_turn
signal enemy_turn
signal turn_play
signal turn_pause


var player:BattleCharacter
var enemy:BattleCharacter

var playerStateUI
var enemyStateUI

var playerPropertyPanel
var enemyPropertyPanel

var skillUI
onready var itemUI = $ui/ItemUI
var tscn_JumpNumber = preload("jumps/JumpNumber.tscn")
var tscn_JumpName = preload("jumps/JumpName.tscn")

var jumpNumberPlace

func _ready():
	jumpNumberPlace = $jumpNumberPlace
	player = $characters/player
	enemy = $characters/enemy
	pass
	
func _process(delta: float) -> void:
	TriggerSystem.sendEvent("process",delta)	

func start(_player,_enemy):
#	player.set(_player)
	enemy.set_enemy(player)
	# 注册信号侦听
	player.connect("attack",self,"onAttack")
	player.connect("jumpNumber",self,"onJumpNumber")
	player.connect("jumpSkillName",self,"onJumpName")
	player.connect("jumpMiss",self,"onJumpMiss")
	player.connect("die",self,"onDie")
	
	enemy.connect("attack",self,"onAttack")
	enemy.connect("jumpNumber",self,"onJumpNumber")
	enemy.connect("jumpSkillName",self,"onJumpName")
	enemy.connect("jumpMiss",self,"onJumpMiss")
	enemy.connect("die",self,"onDie")
	
#	playerStateUI.start(player)
	player.start(self,enemy)
	enemy.start(self,player)
	
	pass
	
func onAttack(fromChara,toChara):
	var dmgObj = DmgObjFactory.createAttackDmg(fromChara,toChara,fromChara.atk)
	BattleProcess.damageProcess(dmgObj)
	
func onJumpNumber(dmgObj,position):
	var jumpNumber = tscn_JumpNumber.instance()
	jumpNumberPlace.add_child(jumpNumber)
	jumpNumber.start(dmgObj,position)

func onJumpName(name,position):
	var jumpName = tscn_JumpName.instance()
	jumpNumberPlace.add_child(jumpName)
	jumpName.start(name,position)
	
func onJumpMiss(position):
	var jumpName = tscn_JumpName.instance()
	jumpNumberPlace.add_child(jumpName)
	jumpName.start("失误",position)	
	
func onJumpPerry(position):
	var jumpName = tscn_JumpName.instance()
	jumpNumberPlace.add_child(jumpName)
	jumpName.start("招架",position)		
	
func onJumpDodge(position):
	var jumpName = tscn_JumpName.instance()
	jumpNumberPlace.add_child(jumpName)
	jumpName.start("躲闪",position)	
	
func onDie(character):
	player.set_process(false)
	enemy.set_process(false)
	# 去除所有触发器
	TriggerSystem.triggerList = []
	# 等待1.5秒
	yield(get_tree().create_timer(1.5),"time_out")
	if character == enemy :
		win()
	else:
		lose()
	
func win():
	emit_signal("win")
	
func lose():
	emit_signal("loose")

		