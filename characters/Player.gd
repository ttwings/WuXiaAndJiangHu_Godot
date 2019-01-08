extends "res://characters/Character.gd"


func _ready():
	# $Balloon.hide()
	pass
	
func _process(delta):
	if can_move:
		for dir in moves.keys():
			if Input.is_action_pressed(dir):
				facing = dir
				move(facing)
	
	if Input.is_action_pressed("A"):
		#attack(facing)
		#$"Balloon/AnimationPlayer".play("ballon05")
		$"Skill/AnimatedSprite".play('default')
		# $Balloon.hide()

	