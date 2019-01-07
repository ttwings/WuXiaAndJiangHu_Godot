extends "res://characters/Character.gd"

func _process(delta):
	if can_move:
		for dir in moves.keys():
			if Input.is_action_pressed(dir):
				facing = dir
				move(facing)
	
	if Input.is_action_pressed("battle_attack"):
		#attack(facing)
		print("attack")

	